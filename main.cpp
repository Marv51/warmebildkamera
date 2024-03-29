#include <QApplication>
#include <QThread>
#include <QMutex>
#include <QMessageBox>

#include <QColor>
#include <QLabel>
#include <QtDebug>
#include <QString>
#include <QPushButton>
#include <QSlider>

#include "LeptonThread.h"
#include "PiCamThread.h"
#include "ControlThread.h"
#include <QShortcut>
#include <QShortcutEvent>
#include <QKeyEvent>
#include <QKeySequence>
#include "MyLabel.h"
#include "gallery.h"
#include </usr/local/include/pigpio.h>

int main( int argc, char **argv )
{
	//create the app
	QApplication a( argc, argv );

    QWidget *myWidget = new QWidget;
    myWidget->setGeometry(640, 480, 340, 290);


	//create an image placeholder for myLabel
	QImage myImage;
    int width = myWidget->width();
    int height = myWidget->height();
    myImage = QImage(width, height, QImage::Format_RGB888);

    //create a label, and set it's image to the placeholder
    MyLabel myLabel(myWidget);
    myLabel.setGeometry(0, 0, 640, 480);
    myLabel.setPixmap(QPixmap::fromImage(myImage));


    Gallery gallery(myWidget);

    QSlider maxValSli(myWidget);
    maxValSli.setGeometry(30, 0, 50, 240);
    maxValSli.setMinimum(8300);
    maxValSli.setMaximum(8600);

    QSlider minValSli(myWidget);
    minValSli.setGeometry(30, 240, 50, 240);
    minValSli.setMinimum(7900);
    minValSli.setMaximum(8200);



    // initialize all GPIO Pins, needed for the SPI Bus and Stuff (pgpio Library)
    gpioInitialise();

    // create all Threads
    ControlThread *controlThread = new ControlThread();
    QObject::connect(controlThread, SIGNAL(updateImage(QImage)), &myLabel, SLOT(setImage(QImage)));
    QObject::connect(controlThread, SIGNAL(savedNewImage()), &gallery, SLOT(refreshPixmap()));

    LeptonThread *thermalThread = new LeptonThread();
    QObject::connect(&minValSli, SIGNAL(valueChanged(int)), thermalThread, SLOT(minValChanged(int)));
    QObject::connect(&maxValSli, SIGNAL(valueChanged(int)), thermalThread, SLOT(maxValChanged(int)));
    QObject::connect(&minValSli, SIGNAL(valueChanged(int)), &myLabel, SLOT(minValChanged(int)));
    QObject::connect(&maxValSli, SIGNAL(valueChanged(int)), &myLabel, SLOT(maxValChanged(int)));
    QObject::connect(thermalThread, SIGNAL(updateImage(QImage)), controlThread, SLOT(setThermalImage(QImage)));
    QObject::connect(thermalThread, SIGNAL(updateImage(QImage)), &myLabel, SLOT(setThermalImage(QImage)));

    PiCamThread *cameraThread = new PiCamThread();
    QObject::connect(cameraThread, SIGNAL(updateImage(QImage)), controlThread, SLOT(setCameraImage(QImage)));

    // start the threads
    controlThread->start();
    cameraThread->start();
    thermalThread->start();

    maxValSli.setSliderPosition(8450);
    minValSli.setSliderPosition(8050);
	
    // start the application into fullscreen
    myWidget->showFullScreen();

    return a.exec();
}

