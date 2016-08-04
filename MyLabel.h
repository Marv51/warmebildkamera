#ifndef MYLABEL_H
#define MYLABEL_H

#include <QtCore>
#include <QWidget>
#include <QLabel>
#include <stdint.h>
#include "LeptonThread.h"

//we extend QLabel to give it an extra slot, setImage
//this is because we can't pass a QPixmap from our thread
//so we have to pass a QImage and turn the QImage into a QPixmap on our end

class MyLabel : public QLabel {
  Q_OBJECT;

  public:
    MyLabel(QWidget *parent = 0);
    ~MyLabel();
   protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

  public slots:
    void setThermalImage(QImage);
    void setImage(QImage);
    void minValChanged(int);
    void maxValChanged(int);

   private:
    QLabel* tempPreviewLabel;
    QImage image;
    int minValue;
    int maxValue;
};

#endif
