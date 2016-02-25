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


	//create a FFC button
//	QPushButton *button1 = new QPushButton("Perform FFC", myWidget);
//	button1->setGeometry(320/2-50, 290-35, 100, 30);

    //create a thread to gather SPI data
	//when the thread emits updateImage, the label should update its image accordingly
    ControlThread *controlThread = new ControlThread();

    LeptonThread *thermalThread = new LeptonThread();
    QObject::connect(thermalThread, SIGNAL(updateImage(QImage)), controlThread, SLOT(setThermalImage(QImage)));

    PiCamThread *cameraThread = new PiCamThread();
    QObject::connect(cameraThread, SIGNAL(updateImage(QImage)), controlThread, SLOT(setCameraImage(QImage)));
    QObject::connect(controlThread, SIGNAL(updateImage(QImage)), &myLabel, SLOT(setImage(QImage)));


	
	//connect ffc button to the thread's ffc action
//	QObject::connect(button1, SIGNAL(clicked()), thread, SLOT(performFFC()));
    controlThread->start();
    cameraThread->start();
    thermalThread->start();
	
    //myWidget->show();
    myWidget->showFullScreen();

	return a.exec();
}

