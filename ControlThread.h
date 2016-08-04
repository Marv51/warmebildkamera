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
#include <QPainter>
#include <QFontMetrics>
#include <QProcess>
#include <stdlib.h>
#include <string>
#include <iostream>
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
  void setZoom(int value);
  void finishedEncoding();

signals:
  void updateImage(QImage);
  void savedNewImage();

private:
    States state;
    QImage thermalImage;
    QImage cameraImage;
    QImage mixedImage;

    QImage image;

    bool hasCameraImage;
    bool hasThermalImage;
    bool Button4Pressed;
    bool Button3Pressed;
    bool Button2Pressed;
    bool recordVideo;
    bool printCameraImage;
    bool printThermalImage;
    int captureCount;
    int showSuccessMsg;
    bool showSaveMsg;
    QImage createMixedImage();
    void emitAndUpdateImage();
    QImage writeTextToImage(QImage, const QString);
    double zoom_value;
    QMutex cameraMutex;
    QMutex thermalMutex;
    std::stringstream stringStream;
};

#endif // CONTROLTHREAD_H
