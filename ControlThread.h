#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H

#include </usr/local/include/pigpio.h>
#include <QImage>
#include <ctime>
#include <time.h>
#include <stdint.h>
#include <QThread>
#include <QtCore>
#include <QPixmap>
#include <QString>
#include <stdlib.h>
#include <QPainter>
#include <string>
#include <sstream>

class ControlThread : public QThread
{
Q_OBJECT;
public:
    ControlThread();
    void run();
    void saveImages();

    enum States{Thermal, Camera, Mixed};
    enum TFTButtons{Button1=17, Button2=22, Button3=23, Button4=27};

public slots:
  void setThermalImage(QImage);
  void setCameraImage(QImage);

signals:
  void updateImage(QImage);

private:
    States state;
    QImage thermalImage;
    QImage cameraImage;
    QImage mixedImage;

    bool hasCameraImage;
    bool hasThermalImage;
    bool Button1Pressed;
    bool Button2Pressed;
    bool printCameraImage;
    bool printThermalImage;
    int captureCount;
    QImage createMixedImage();
    QMutex cameraMutex;
    QMutex thermalMutex;
    std::stringstream stringStream;
};

#endif // CONTROLTHREAD_H
