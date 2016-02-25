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

    if(wiringPiSetup()){
        qDebug() << "wiringSetup Failed" << endl;
        return;
    }

    mixedImage = QImage(640, 480 , QImage::Format_ARGB32_Premultiplied);

    state = Thermal;
    hasCameraImage = false;
    hasThermalImage = false;
    Button1Pressed = false;
    Button2Pressed = false;

    printCameraImage = false;
    printThermalImage = false;

    pinMode(Button1, INPUT);
    pinMode(Button2, INPUT);
    pinMode(Button3, INPUT);
    pinMode(Button4, INPUT);

    pullUpDnControl(Button1, PUD_UP);
    pullUpDnControl(Button2, PUD_UP);
    pullUpDnControl(Button3, PUD_UP);
    pullUpDnControl(Button4, PUD_UP);

    captureCount = 0;
    while(true){

        if(digitalRead(Button4) == LOW && !Button1Pressed){
            Button1Pressed = true;
//            qDebug() << "switch" << endl;
            state = (States)((state+1)%3); //%2 disables mixed mode, change to %3 for using mixed mode.

        } else if(digitalRead(Button4) == HIGH){
            Button1Pressed = false;
        }

        if(digitalRead(Button3) == LOW && !Button2Pressed) {
            printCameraImage = true;
            printThermalImage = true;
            qDebug() << "printImages" << endl;
        } else if(digitalRead(Button3) == HIGH){
            Button2Pressed = false;
        }

        switch (state){
            case Thermal:
                if(hasThermalImage){
                    emit updateImage(thermalImage);
//                    qDebug() << "Setting CameraFrame" << endl;
                    hasThermalImage = false;
                }
                break;
            case Camera:
                if(hasCameraImage){
                    emit updateImage(cameraImage);
//                    qDebug() << "Setting CameraFrame" << endl;
                    hasCameraImage = false;
                }
                break;

            case Mixed:
                if(hasCameraImage && hasThermalImage){
                    emit updateImage(createMixedImage());
                    hasCameraImage = false;
                    hasThermalImage = false;
                }
                break;
        }

    }
}

void ControlThread::setThermalImage(QImage image){
    thermalImage = image;
    if(printThermalImage){
        thermalImage.save("/home/pi/thermal.png");
//      thermalImage.save(QString("home/pi/thermal%1.png").arg(captureCount).toStdString().c_str());
        printThermalImage = false;
    }

    hasThermalImage = true;
}

void ControlThread::setCameraImage(QImage image){
    cameraImage = image;
    if(printCameraImage){
        cameraImage.save("/home/pi/camera.png");
//        cameraImage.save(QString("home/pi/camera%1.png").arg(captureCount).toStdString().c_str());
        printCameraImage = false;
    }
    hasCameraImage = true;
}


