#ifndef GALLERY_H
#define GALLERY_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QProcess>
#include <QDir>

class Gallery : public QLabel
{
    Q_OBJECT
public:
    Gallery(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent*);

public slots:
    void refreshPixmap();

private slots:
    void showPrevImage();
    void showNextImage();
    void changeImageMode();
    void closeGallery();
    void deleteCurrentImages();
    void showLastVideo();

private:
    QFileInfoList getImageList();
    bool fullscreen;
    int viewIndex;
    QPixmap pixmap;
    int imageMode;
};

#endif // GALLERY_H
