#include <iostream>
#include "gallery.h"

Gallery::Gallery(QWidget *parent) : QLabel(parent), fullscreen(false), viewIndex(0), imageMode(0){
    QPushButton* prev = new QPushButton("<", this);
    prev->move(120, 390);
    prev->resize(120, 60);
    QObject::connect(prev, SIGNAL(released()), this, SLOT(showPrevImage()));

    QPushButton* next = new QPushButton(">", this);
    next->move(380, 390);
    next->resize(120, 60);
    QObject::connect(next, SIGNAL(released()), this, SLOT(showNextImage()));

    QPushButton* mode = new QPushButton("*", this);
    mode->move(250, 390);
    mode->resize(120, 60);
    QObject::connect(mode, SIGNAL(released()), this, SLOT(changeImageMode()));

    QPushButton* close = new QPushButton("x", this);
    close->move(540, 10);
    close->resize(60, 60);
    QObject::connect(close, SIGNAL(released()), this, SLOT(closeGallery()));

    QPushButton* delButton = new QPushButton("Del", this);
    delButton->move(10, 390);
    delButton->resize(60, 60);
    QObject::connect(delButton, SIGNAL(released()), this, SLOT(deleteCurrentImages()));

    QPushButton* vidBUtton = new QPushButton("Video", this);
    vidBUtton->move(280, 10);
    vidBUtton->resize(60, 60);
    QObject::connect(vidBUtton, SIGNAL(released()), this, SLOT(showLastVideo()));

    this->setStyleSheet("QPushButton {background-color: rgba(255,255,255,127)}");
    closeGallery();
}

void Gallery::mousePressEvent(QMouseEvent *){
    if (!fullscreen && getImageList().size() != 0){
        this->move(10,10);
        this->resize(620, 460);
        QWidget::raise();
        fullscreen = true;
        refreshPixmap();
    }
}

void Gallery::closeGallery(){
    this->move(570, 410);
    this->resize(60, 60);
    fullscreen = false;
    viewIndex = 0;
    imageMode = 0;
    refreshPixmap();
}


void Gallery::refreshPixmap() {
    if (getImageList().size() <= viewIndex*3+imageMode) return;

    QImage currentImage = QImage(getImageList().at(viewIndex*3+imageMode).absoluteFilePath());
    pixmap = QPixmap::fromImage(currentImage);
    int w = this->width();
    int h = this->height();
    setPixmap(pixmap.scaled(w, h, Qt::IgnoreAspectRatio));
}

QFileInfoList Gallery::getImageList() {
    QDir dir = QDir("/home/pi/share");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters(QStringList() << "*.png");
    dir.setSorting(QDir::Name | QDir::Reversed);
    return dir.entryInfoList();
}

void Gallery::showPrevImage(){
    viewIndex = (viewIndex + 1) % (getImageList().size() / 3);
    refreshPixmap();
}

void Gallery::showNextImage(){
    viewIndex = (viewIndex - 1);
    if (viewIndex < 0){
        viewIndex = (getImageList().size() / 3) - 1;
    }
    refreshPixmap();
}

void Gallery::changeImageMode() {
    imageMode = (imageMode+1)%3;
    refreshPixmap();
}

void Gallery::deleteCurrentImages() {
    QDir dir = QDir("/home/pi/share");
    QFileInfoList list = getImageList();
    for (int i = 0; i < 3; i++) {
        dir.remove(list.at(viewIndex*3+i).fileName());
    }
    if (getImageList().size() == 0) closeGallery();
    else showPrevImage();

}

void Gallery::showLastVideo() {
    QProcess* proc = new QProcess();
    proc->start("omxplayer", QStringList() << "/home/pi/share/test.avi");

}

