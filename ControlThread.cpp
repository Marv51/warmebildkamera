#include "ControlThread.h"

ControlThread::ControlThread() : QThread()
{
}

QImage ControlThread::createMixedImage(){
    QPainter painter(&mixedImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(mixedImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, cameraImage.scaled(mixedImage.size()));
    painter.setCompositionMode(QPainter::CompositionMode_Overlay);
    painter.drawImage(0, 0, thermalImage.scaled(mixedImage.size()));
    painter.end();

    return mixedImage;
}

void ControlThread::run(){

    mixedImage = QImage(640, 480 , QImage::Format_ARGB32_Premultiplied);

    state = Mixed;
    hasCameraImage = false;
    hasThermalImage = false;
    Button1Pressed = false;
    Button2Pressed = false;

    printCameraImage = false;
    printThermalImage = false;

    gpioSetMode(Button1, PI_INPUT);
    gpioSetMode(Button2, PI_INPUT);
    gpioSetMode(Button3, PI_INPUT);
    gpioSetMode(Button4, PI_INPUT);

    gpioSetPullUpDown(Button1, PI_PUD_UP);
    gpioSetPullUpDown(Button2, PI_PUD_UP);
    gpioSetPullUpDown(Button3, PI_PUD_UP);
    gpioSetPullUpDown(Button4, PI_PUD_UP);

    int buttonTimer = 0;

    captureCount = 0;
    while(true){

        buttonTimer ++;

        if (buttonTimer >= 10000)
        {
            buttonTimer = 0;

            if(gpioRead(Button4) == PI_LOW && !Button1Pressed){
                Button1Pressed = true;
                //qDebug() << "switch" << endl;
                state = (States)((state+1)%3); //%2 disables mixed mode, change to %3 for using mixed mode.

            } else if(gpioRead(Button4) == PI_HIGH){
                Button1Pressed = false;
            }

            if(gpioRead(Button3) == PI_LOW && !Button2Pressed) {
                printCameraImage = true;
                printThermalImage = true;
                qDebug() << "printImages" << endl;
            } else if(gpioRead(Button3) == PI_HIGH){
                Button2Pressed = false;
            }
        }

        switch (state){
            case Thermal:
                if(hasThermalImage){
                    thermalMutex.lock();
                    emit updateImage(thermalImage);
                    thermalMutex.unlock();
//                    qDebug() << "Setting CameraFrame" << endl;
                    hasThermalImage = false;
                }
                break;
            case Camera:
                if(hasCameraImage){
                    cameraMutex.lock();
                    emit updateImage(cameraImage);
                    cameraMutex.unlock();
//                    qDebug() << "Setting CameraFrame" << endl;
                    hasCameraImage = false;
                }
                break;

            case Mixed:
                if(hasCameraImage && hasThermalImage){
                    cameraMutex.lock();
                    thermalMutex.lock();
                    emit updateImage(createMixedImage());
                    cameraMutex.unlock();
                    thermalMutex.unlock();
                    hasCameraImage = false;
                    hasThermalImage = false;
                }
                break;
        }

    }
}

void ControlThread::setThermalImage(QImage image){
    thermalMutex.lock();
    thermalImage = image;
    thermalMutex.unlock();
    if(printThermalImage){
        thermalImage.save("/home/pi/thermal.png");
//      thermalImage.save(QString("home/pi/thermal%1.png").arg(captureCount).toStdString().c_str());
        printThermalImage = false;
    }

    hasThermalImage = true;
}

void ControlThread::setCameraImage(QImage image){
    cameraMutex.lock();
    cameraImage = image;
    cameraMutex.unlock();
    usleep(5);
    if(printCameraImage){
        cameraImage.save("/home/pi/camera.png");
//        cameraImage.save(QString("home/pi/camera%1.png").arg(captureCount).toStdString().c_str());
        printCameraImage = false;
    }
    hasCameraImage = true;
}


