#include "PiCamThread.h"
#include <fstream>

PiCamThread::PiCamThread() : QThread()
{
}

void processCommandLine (raspicam::RaspiCam &Camera ) {
    Camera.setWidth (1280);
    Camera.setHeight ( 960);
    Camera.setBrightness ( 50);
    Camera.setRotation(180);
    Camera.setSharpness ( 0);
    Camera.setContrast ( 0);
    Camera.setSaturation ( 0);
    Camera.setShutterSpeed( 0);
    Camera.setISO (400);

    Camera.setVideoStabilization ( true );
    Camera.setExposureCompensation ( 1 );

    Camera.setAWB_RB(1, 1);

}


void PiCamThread::run()
{
    raspicam::RaspiCam Camera; //Cmaera object

    processCommandLine(Camera);
    //Open camera
    //cout<<"Opening Camera..."<<endl;
    if ( !Camera.open()) {
        qDebug()<<"Error opening camera"<<endl;
        return;
    }
    //wait a while until camera stabilizes
    //cout<<"Sleeping for 3 secs"<<endl;
    //sleep(3);
    myImage = QImage(Camera.getWidth(),Camera.getHeight() , QImage::Format_RGB888);
    while(true) {

        //Camera.setCaptureSize(640, 480);



//        printf("Size: %d", Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ));
        //allocate memory
        //15 chars extra for the header of the ppm file
        unsigned char *data=new unsigned char[  Camera.getImageBufferSize( )];
        std::string header = "P6\n 1280 960 255\n";
        //extract the image in rgb format
        Camera.grab();
        Camera.retrieve(data);
        QRgb color;

        header.append((char*)data, Camera.getImageBufferSize( ));
//        std::ofstream outFile ("raspicam_image.ppm" , std::ios::binary);
//        outFile<<"P6\n"<<Camera.getWidth() << " "<< Camera.getHeight() << " 255\n";
//        outFile.write( (char*) data, Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));


        myImage.loadFromData((const unsigned char * )header.c_str(), header.length(), "PPM");

//        for(unsigned int i = 0; i<Camera.getWidth(); i= i+3){
//            for(unsigned int j = 0; j<Camera.getHeight();j++){
//              color = qRgb(data[(i*Camera.getWidth() + j)*3], data[(i*Camera.getWidth() + j)*3] + 1, data[(i*Camera.getWidth() + j)*3] + 2);

//              myImage.setPixel(i, j, color);
//                  //printf("%d, %d, %d \n", Camera.getHeight(), Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ), Camera.getWidth() + j)*3]);
//            }
//        }

        //lets emit the signal for update
        emit updateImage(myImage);
//        myImage.save("/home/pi/test.png");
        delete data;
//        break;
    }

    Camera.release();

}
