#include "MyLabel.h"
#include <QColor>
#include <iostream>
#include <stdint.h>
#include <QFontMetrics>
#include <QMouseEvent>
#include "Palettes.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent), minValue(7900), maxValue(8300)
{
}
MyLabel::~MyLabel()
{
}

//when the system calls setImage, we'll set the label's pixmap
void MyLabel::setImage(QImage image) {
    QPixmap pixmap = QPixmap::fromImage(image);

    int w = this->width();
    int h = this->height();
    setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
}

void MyLabel::setThermalImage(QImage image) {
    this->image = image;
}

void MyLabel::mouseReleaseEvent(QMouseEvent*) {
    delete tempPreviewLabel;
}

void MyLabel::mousePressEvent(QMouseEvent *ev) {

    const QColor color = image.pixel(ev->x() / 8, ev->y() / 8);

    int minDistI = -1;
    int minDist = 1000;
    for (int i = 0; i < 255; i+= 1){
        int dist = (abs(colormap_ironblack[3*i] - color.red()) +
                abs(colormap_ironblack[3*i+1] - color.green()) +
                abs(colormap_ironblack[3*i+2] - color.blue()));
        if (dist < minDist) {
            minDist = dist;
            minDistI = i;
        };

    }
    int orgTempValue = minDistI / (255.0 / (double)(maxValue - minValue)) + minValue;

    double tempGuess = (orgTempValue - 7900) / 15;
    double percent = minDistI / 255.0 * 100;

    QChar degree(0260); // Angle/Degree Symbol strange unicode stuff.
    QString temp = QString("%1%3C (%2\%)").arg(tempGuess, 0, 'f', 1).arg(percent, 0, 'f', 0).arg(degree);


    tempPreviewLabel = new QLabel(this);
    QFont font = tempPreviewLabel->font();
    font.setPointSize(24);
    tempPreviewLabel->setFont(font);
    QFontMetrics fm(font);

    tempPreviewLabel->setStyleSheet("QLabel { background-color: black; color: white; padding: 5 2 5 2; }");

    tempPreviewLabel->setGeometry(ev->x(), ev->y(), fm.width(temp) + 15, 34);
    tempPreviewLabel->setText(temp);
    tempPreviewLabel->show();
}

void MyLabel::minValChanged(int input) {
    minValue = input;
}

void MyLabel::maxValChanged(int input) {
    maxValue = input;
}
