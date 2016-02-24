#include "LeptonThread.h"

#include "Palettes.h"
#include "SPI.h"
#include "Lepton_I2C.h"

#define PACKET_SIZE 164
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define PACKETS_PER_FRAME 60
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)
#define FPS 27;


LeptonThread::LeptonThread() : QThread()
{
}

LeptonThread::~LeptonThread() {
}

void LeptonThread::run()
{
    thermal = false;

	//open spi port
    //SpiOpenPort(0);
    int fd;
    gpioInitialise();
    fd = spiOpen(1, 8000000, (1<<8)|(1<<4) | 3);
    char txBuf[PACKET_SIZE] = {0, };
    char rxBuf[PACKET_SIZE * PACKETS_PER_FRAME];

    raspicam::RaspiCam Camera; //Cmaera object
    //Open camera
    //cout<<"Opening Camera..."<<endl;
    Camera.open();
    //if ( !Camera.open()) {cerr<<"Error opening camera"<<endl;return -1;}
    //wait a while until camera stabilizes
    //cout<<"Sleeping for 3 secs"<<endl;
    sleep(3);

    while(true) {
        myImage = QImage(80, 60, QImage::Format_RGB888);
        if(thermal){
            //read data packets from lepton over SPI
            int resets = 0;
            for(int j=0;j<PACKETS_PER_FRAME;j++) {
                //if it's a drop packet, reset j to 0, set to -1 so he'll be at 0 again loop
                //read(spi_cs0_fd, result+sizeof(uint8_t)*PACKET_SIZE*j, sizeof(uint8_t)*PACKET_SIZE);
                spiXfer(fd, txBuf, rxBuf + j*PACKET_SIZE, PACKET_SIZE);

                int packetNumber = rxBuf[j*PACKET_SIZE + 1];
                if(packetNumber != j) {
                    j = -1;
                    resets += 1;
                    usleep(1000);
                    //Note: we've selected 750 resets as an arbitrary limit, since there should never be 750 "null" packets between two valid transmissions at the current poll rate
                    //By polling faster, developers may easily exceed this count, and the down period between frames may then be flagged as a loss of sync
                    if(resets == 750) {
                        spiClose(fd);
                        usleep(750000);
                        fd = spiOpen(1, 8000000, (1<<8)|(1<<4) | 3);

                    }
                }
            }
            if(resets >= 30) {
                qDebug() << "done reading, resets: " << resets;
            }

            frameBuffer = (uint16_t *)rxBuf;
            int row, column;
            uint16_t value;
            uint16_t minValue = 65535;
            uint16_t maxValue = 0;


            for(int i=0;i<FRAME_SIZE_UINT16;i++) {
                //skip the first 2 uint16_t's of every packet, they're 4 header bytes
                if(i % PACKET_SIZE_UINT16 < 2) {
                    continue;
                }

                //flip the MSB and LSB at the last second
                int temp = rxBuf[i*2];
                rxBuf[i*2] = rxBuf[i*2+1];
                rxBuf[i*2+1] = temp;

                value = frameBuffer[i];
                if(value > maxValue) {
                    maxValue = value;
                }
                if(value < minValue) {
                    minValue = value;
                }
                column = i % PACKET_SIZE_UINT16 - 2;
                row = i / PACKET_SIZE_UINT16 ;
            }

            float diff = maxValue - minValue;
            float scale = 255/diff;
            QRgb color;
            for(int i=0;i<FRAME_SIZE_UINT16;i++) {
                if(i % PACKET_SIZE_UINT16 < 2) {
                    continue;
                }
                value = (frameBuffer[i] - minValue) * scale;
                const int *colormap = colormap_rainbow;
                color = qRgb(colormap[3*value], colormap[3*value+1], colormap[3*value+2]);
                column = (i % PACKET_SIZE_UINT16 ) - 2;
                row = i / PACKET_SIZE_UINT16;
                myImage.setPixel(column, row, color);
            }
        } else {
            //capture
            Camera.grab();
            myImage = QImage(Camera.getWidth(),Camera.getHeight() , QImage::Format_RGB888);
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

        }

		//lets emit the signal for update
		emit updateImage(myImage);

	}
	
	//finally, close SPI port just bcuz
    //SpiClosePort(0);
    spiClose(fd);
}

void LeptonThread::performFFC() {
	//perform FFC
    //lepton_perform_ffc();
}
