#ifndef TEXTTHREAD
#define TEXTTHREAD

#include <ctime>
#include <stdint.h>
#include </usr/local/include/pigpio.h>

#include <QThread>
#include <QtCore>
#include <QPixmap>
#include <QImage>

#define PACKET_SIZE 164
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define PACKETS_PER_FRAME 60
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)

class LeptonThread : public QThread
{
  Q_OBJECT;

public:
  LeptonThread();
  ~LeptonThread();
  uint16_t *frameBuffer;
  void run();

public slots:
  void minValChanged(int);
  void maxValChanged(int);

signals:
  void updateText(QString);
  void updateImage(QImage);

private:
  QImage myImage;

  uint8_t result[PACKET_SIZE*PACKETS_PER_FRAME];


  int minValue;
  int maxValue;

};

#endif
