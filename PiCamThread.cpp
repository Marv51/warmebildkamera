#include "PiCamThread.h"

PiCamThread::PiCamThread() : QThread()
{
}


void PiCamThread::run()
{
    raspicam::RaspiCam Camera; //Cmaera object
    //Open camera
    //cout<<"Opening Camera..."<<endl;
    Camera.open();
    if ( !Camera.open()) {
        qDebug()<<"Error opening camera"<<endl;
        return;
    }
    //wait a while until camera stabilizes
    //cout<<"Sleeping for 3 secs"<<endl;
    sleep(3);

    while(true) {
        myImage = QImage(Camera.getWidth(),Camera.getHeight() , QImage::Format_RGB888);

        //capture
        Camera.grab();

        printf("Size: %d", Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ));
        //allocate memory
        int bytes = Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB );
        unsigned char *data=new unsigned char[bytes];
        //extract the image in rgb format
        QRgb color;
        Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );//get camera image
        for(unsigned int i = 0; i<Camera.getWidth(); i= i+3){
            for(unsigned int j = 0; j<Camera.getHeight();j++){
              color = qRgb(data[(i*Camera.getWidth() + j)*3], data[(i*Camera.getWidth() + j)*3] + 1, data[(i*Camera.getWidth() + j)*3] + 2);

              myImage.setPixel(i, j, color);
//                  printf("%d, %d, %d \n", Camera.getHeight(), Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ), Camera.getWidth() + j)*3]);
            }
        }

        //lets emit the signal for update
        emit updateImage(myImage);

    }

}
