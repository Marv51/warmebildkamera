#include "PiCamThread.h"
#include <fstream>

PiCamThread::PiCamThread() : QThread()
{
}

// initializes the camera, it wont't run without this!
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

// Thread for communicating with the raspberry camera
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
    unsigned char *data=new unsigned char[  Camera.getImageBufferSize( )];

    while(true) {

        // setting header for ppm image, this is needed to save it directly into a QImage
        std::string header = "P6\n 1280 960 255\n";

        //take a picture and retrieve the data from the buffer in the camera
        Camera.grab();
        Camera.retrieve(data);

        // combines the header and the camera data and saves it into a QImage
        header.append((char*)data, Camera.getImageBufferSize( ));
        myImage.loadFromData((const unsigned char * )header.c_str(), header.length(), "PPM");

        //lets emit the signal for update
        emit updateImage(myImage);        
    }
    delete data;
    Camera.release();
}
