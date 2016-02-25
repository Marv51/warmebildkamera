#include <QApplication>
#include <QThread>
#include <QMutex>
#include <QMessageBox>

#include <QColor>
#include <QLabel>
#include <QtDebug>
#include <QString>
#include <QPushButton>

#include "LeptonThread.h"
#include "PiCamThread.h"
#include "ControlThread.h"
#include <QShortcut>
#include <QShortcutEvent>
#include <QKeyEvent>
#include <QKeySequence>
#include "MyLabel.h"
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

    gpioInitialise();

    ControlThread *controlThread = new ControlThread();
    QObject::connect(controlThread, SIGNAL(updateImage(QImage)), &myLabel, SLOT(setImage(QImage)));

    LeptonThread *thermalThread = new LeptonThread();
    QObject::connect(thermalThread, SIGNAL(updateImage(QImage)), controlThread, SLOT(setThermalImage(QImage)));

    PiCamThread *cameraThread = new PiCamThread();
    QObject::connect(cameraThread, SIGNAL(updateImage(QImage)), controlThread, SLOT(setCameraImage(QImage)));

    controlThread->start();
    cameraThread->start();
    thermalThread->start();
	
    myWidget->showFullScreen();

	return a.exec();
}

