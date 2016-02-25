#include "PiCamThread.h"
#include <fstream>

PiCamThread::PiCamThread() : QThread()
{
}

void initCamera(raspicam::RaspiCam &Camera ) {
    Camera.setWidth (1280);
    Camera.setHeight ( 960);
    Camera.setBrightness ( 50);
    Camera.setRotation(180);
    Camera.setSharpness ( 0);
    Camera.setContrast ( 0);
    Camera.setSaturation ( 0);
    Camera.setShutterSpeed( 0);
    Camera.setISO (400);

    Camera.setVideoStabilization ( false );
    Camera.setExposureCompensation ( 1 );

    Camera.setAWB_RB(1, 1);

}


void PiCamThread::run()
{
    raspicam::RaspiCam Camera;

    initCamera(Camera);
    //Open camera
    if ( !Camera.open()) {
        qDebug()<<"Error opening camera"<<endl;
        return;
    }

    myImage = QImage(Camera.getWidth(),Camera.getHeight() , QImage::Format_RGB888);
    while(true) {

        unsigned char *data=new unsigned char[  Camera.getImageBufferSize( )];
        // setting header for ppm image
        std::string header = "P6\n 1280 960 255\n";
        //extract the image in rgb format
        Camera.grab();
        Camera.retrieve(data);

        header.append((char*)data, Camera.getImageBufferSize( ));
        myImage.loadFromData((const unsigned char * )header.c_str(), header.length(), "PPM");
        //lets emit the signal for update
        emit updateImage(myImage);
        delete data;
    }

    Camera.release();

}
