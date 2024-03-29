#include "ControlThread.h"

ControlThread::ControlThread() : QThread(), recordVideo(false)
{
}

// creates a mixed image from the thermal and camera as overlay
QImage ControlThread::createMixedImage(){
    QPainter painter(&mixedImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(mixedImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);


    //const int cut_off = 30;
    //painter.drawImage(0, 0, cameraImage.copy(cut_off, cut_off, cameraImage.height() - 2 * cut_off, cameraImage.width() - 2 * cut_off).scaled(mixedImage.size()));
    float cut_off = (float)zoom_value;
    QRect rect = QRect(cameraImage.width() * cut_off,  cameraImage.height() * cut_off,
                          cameraImage.width() - cameraImage.width() * 2 * cut_off, cameraImage.height() - cameraImage.height() * 2 * cut_off);
    painter.drawImage(0, 0, cameraImage.copy(rect).scaled(mixedImage.size()));
    // the is the overlay mode, could be changed for other mixed images
    painter.setCompositionMode(QPainter::CompositionMode_Overlay);
    painter.drawImage(0, 0, thermalImage.scaled(mixedImage.size()));
    painter.end();

    return mixedImage;
}

void ControlThread::emitAndUpdateImage() {
    bool hasImage = false;

    // check which camera image should be shown on the screen
    switch (state){
        case Thermal:
            if(hasThermalImage){
                thermalMutex.lock();
                image = thermalImage;
                thermalMutex.unlock();
                hasThermalImage = false;
                hasImage = true;
            }
            break;
        case Camera:
            if(hasCameraImage){
                cameraMutex.lock();
                image = cameraImage;
                cameraMutex.unlock();
                hasCameraImage = false;
                hasImage = true;
            }
            break;

        case Mixed:
            if(hasCameraImage && hasThermalImage){
                cameraMutex.lock();
                thermalMutex.lock();
                image = createMixedImage();
                cameraMutex.unlock();
                thermalMutex.unlock();
                hasCameraImage = false;
                hasThermalImage = false;
                hasImage = true;
            }
            break;
    }


    if (hasImage) {

        image = image.scaled(640, 480, Qt::KeepAspectRatio);

        if (recordVideo) {
            QString time = QString::number(QDateTime::currentMSecsSinceEpoch());
            image.save(QString("/home/pi/share/video_files/frame_%1.bmp").arg(time), 0, 100);
            image = writeTextToImage(image, "rec...");
        }

        if (showSuccessMsg > 0) {
            showSuccessMsg--;
            image = writeTextToImage(image, "Image saved!");
        }

        emit updateImage(image);
    }
}

void ControlThread::setZoom(int value){
    zoom_value = value / 100.0;
}

QImage ControlThread::writeTextToImage(QImage img, const QString str){
    QPainter painter(&img);
    QFont font = painter.font();
    font.setPointSize(32);
    QFontMetrics fm(font);
    painter.setFont(font);

    painter.fillRect(55, 228, fm.width(str) + 10, -40, Qt::black);
    painter.setPen(Qt::white);
    painter.drawText(60, 224, str);
    painter.end();
    return img;
}

void ControlThread::run(){

    zoom_value = 0;
    mixedImage = QImage(640, 480 , QImage::Format_ARGB32_Premultiplied);
    showSuccessMsg = 0;
    showSaveMsg = false;

    state = Thermal;
    hasCameraImage = false;
    hasThermalImage = false;
    Button4Pressed = false;
    Button3Pressed = false;
    Button2Pressed = false;

    printCameraImage = false;
    printThermalImage = false;


    // sets all input pins for the tft buttons
    gpioSetMode(Button1, PI_INPUT);
    gpioSetMode(Button2, PI_INPUT);
    gpioSetMode(Button3, PI_INPUT);
    gpioSetMode(Button4, PI_INPUT);

    // adafruit tft needs a PullUp High for the buttons
    gpioSetPullUpDown(Button1, PI_PUD_UP);
    gpioSetPullUpDown(Button2, PI_PUD_UP);
    gpioSetPullUpDown(Button3, PI_PUD_UP);
    gpioSetPullUpDown(Button4, PI_PUD_UP);

    int buttonTimer = 0;

    captureCount = 0;

    while(true){

        buttonTimer ++;

        // don't look at the buttons all the time
        if (buttonTimer >= 10)
        {
            buttonTimer = 0;

            // due to the PullHigh, High and Low are switched
            // PI_LOW == Button pressend
            // PI_HIGH == Button not pressend

            if(gpioRead(Button4) == PI_LOW && !Button4Pressed && !recordVideo){
                Button4Pressed = true;
                // change state to show different Image
                state = (States)((state+1)%3);

            } else if(gpioRead(Button4) == PI_HIGH){
                Button4Pressed = false;
            }

            if(gpioRead(Button3) == PI_LOW && !Button3Pressed && !recordVideo) {
                Button3Pressed = true;
                saveImages();
//              qDebug() << "printImages" << endl;
            } else if(gpioRead(Button3) == PI_HIGH){
                Button3Pressed = false;
            }

            if(gpioRead(Button2) == PI_LOW && !Button2Pressed) {
                Button2Pressed = true;
                recordVideo = !recordVideo;
                if (!recordVideo) {
                    QProcess* proc = new QProcess();

                    QObject::connect(proc, SIGNAL(finished(int)), this, SLOT(finishedEncoding()));
                    proc->start("./ffmpeg.sh", QStringList());

                    emit updateImage(writeTextToImage(image, "Saving..."));
                    proc->waitForFinished();
                    emit updateImage(image);

                }

            } else if(gpioRead(Button2) == PI_HIGH){
                Button2Pressed = false;
            }
        }

        // check which camera image should be shown on the screen
        emitAndUpdateImage();
        // short sleep, prevents button toggeling
        // also good for keeping frames around 30 fps
        usleep(1000);
    }
}

// saves all 3 images wiht the current timestamp to the share folder
void ControlThread::saveImages(){

    cameraMutex.lock();
    thermalMutex.lock();

    showSaveMsg = true;

    emit updateImage(writeTextToImage(image, "Saving..."));

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");

    if(!thermalImage.isNull()){
        thermalImage.save(QString("/home/pi/share/%1-thermal.png").arg(time), 0, 75);
    }
    if(!cameraImage.isNull()){
        cameraImage.save(QString("/home/pi/share/%1-camera.png").arg(time), 0, 75);
    }
    createMixedImage().save(QString("/home/pi/share/%1-mixed.png").arg(time), 0, 75);

    showSuccessMsg = 15;
    emit savedNewImage();

    cameraMutex.unlock();
    thermalMutex.unlock();
}

// sets the Thermal Image
void ControlThread::setThermalImage(QImage image){
    if (thermalMutex.tryLock(10))
    {
        thermalImage = image;
        thermalMutex.unlock();
        hasThermalImage = true;
    }
}

// sets the Camera Image
void ControlThread::setCameraImage(QImage image){
    if (cameraMutex.tryLock(10))
    {
        cameraImage = image;
        cameraMutex.unlock();
        // sleep a bit or it will be to fast for the control thread
        usleep(5);
        hasCameraImage = true;
    }
}

void ControlThread::finishedEncoding(){
    std::cout << "Hallo" << std::endl;
}


