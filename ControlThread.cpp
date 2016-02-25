#include "ControlThread.h"

ControlThread::ControlThread() : QThread()
{
}

void ControlThread::run(){
    wiringPiSetup();
    state = Camera;
    hasCameraImage = false;
    hasThermalImage = false;
    while(true){
        switch (state){
            case Thermal:
                if(hasThermalImage){
                    emit updateImage(thermalImage);
                    hasThermalImage = false;
                }
                break;
            case Camera:
                if(hasCameraImage){
                    emit updateImage(cameraImage);
                    qDebug() << "Setting CameraFrame" << endl;
                    hasCameraImage = false;
                }
                break;

            case Mixed:
                //Do Nothing
                break;
        }

    }
}

void ControlThread::setThermalImage(QImage image){
    thermalImage = image;
    hasThermalImage = true;
}

void ControlThread::setCameraImage(QImage image){
    cameraImage = image;
    hasCameraImage = true;
}


