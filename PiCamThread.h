#ifndef PICAMTHREAD_H
#define PICAMTHREAD_H

#include <ctime>
#include <stdint.h>

#include <QThread>
#include <QtCore>
#include <QPixmap>
#include <QImage>
#include <QTime>

#include </usr/local/include/raspicam/raspicam.h>

class PiCamThread : public QThread
{
    Q_OBJECT
public:
    PiCamThread();

    void run();

signals:
    void updateText(QString);
    void updateImage(QImage);

public slots:

private:
  QImage myImage;

};

#endif // PICAMTHREAD_H
