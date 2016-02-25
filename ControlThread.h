#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H

#include <wiringPi.h>
#include <pigpio.h>
#include <QImage>
#include <ctime>
#include <stdint.h>
#include <QThread>
#include <QtCore>
#include <QPixmap>
#include <QString>
#include <stdlib.h>
#include <QPainter>

class ControlThread : public QThread
{
Q_OBJECT;
public:
    ControlThread();
    void run();

    enum States{Thermal, Camera, Mixed};
    //Button 1: gpioPin 17, Button 2: gpioPin 22, Button 3: gpioPin 23, Button 4: gpioPin 27
    enum TFTButtons{Button1=0, Button2=3, Button3=4, Button4=2}; //This crap was defined by wiringPi library

public slots:
  void setThermalImage(QImage);
  void setCameraImage(QImage);

signals:
  void updateImage(QImage);

private:
    States state;
    QImage thermalImage;
    QImage cameraImage;
    bool hasCameraImage;
    bool hasThermalImage;
    bool Button1Pressed;
    bool Button2Pressed;
    bool printCameraImage;
    bool printThermalImage;
    int captureCount;
    QImage createMixedImage();
};

#endif // CONTROLTHREAD_H
