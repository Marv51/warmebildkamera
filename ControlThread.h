#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H

#include <wiringPi.h>
#include <QImage>
#include <ctime>
#include <stdint.h>
#include <QThread>
#include <QtCore>
#include <QPixmap>

class ControlThread : public QThread
{
Q_OBJECT;
public:
    ControlThread();
    void run();

    enum States{Thermal, Camera, Mixed};

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
};

#endif // CONTROLTHREAD_H
