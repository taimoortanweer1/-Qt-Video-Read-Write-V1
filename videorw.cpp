#include "videorw.h"

videorw::videorw(QObject *parent) : QObject(parent)
{

}

videorw::videorw(VideoCapture *vcap, cv::String deststr)
{
    inputVideo = vcap;
    this->start = start;
    this->destString = deststr;

    codec = static_cast<int>(inputVideo->get(CAP_PROP_FOURCC));     // Get Codec Type- Int form
    sizeOfVideo = Size((int) inputVideo->get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
                       (int) inputVideo->get(CAP_PROP_FRAME_HEIGHT));

    outputVideo.open(destString + ".avi", codec, inputVideo->get(CAP_PROP_FPS), sizeOfVideo, true);

    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << endl;
    }
}

void videorw::getturretimg(float azi,float elev, Mat IMG, bool enable)
//void videorw::getturretimg(Mat IMG)
{

    Mat src;
    //Mat src;// = cv::Mat(img.height(),img.width(),QImage::Format_RGB888);


    if(enable)
    {

        src = IMG;

        if (src.empty())
        {
            cout << "Finished writing" << endl;
        }
        else
        {
            imshow("video",src);
            cout << azi << " ----- " << elev << endl;
            waitKey(1);
            outputVideo.write(src); //save or

            cout << "imshow received" << endl;

        }
    }
}

void videorw::getturretimgQ(float azi,float elev, QImage Img, bool enable)
//void videorw::getturretimg(Mat IMG)
{


    if(enable)
    {

        Mat src = cv::Mat(Img.height(), Img.width(), QImage::Format_RGB888, const_cast<uchar*>(Img.bits()), Img.bytesPerLine()).clone();
        //Mat src = cv::Mat(Img.height(), Img.width(), QImage::Format_RGB888, Img.bits(), Img.bytesPerLine());

        if (src.empty())
        {
            cout << "Finished writing" << endl;
        }
        else
        {
            cout << "imshow received" << endl;

            //cv::imshow("video",src);
            cout << azi << " ----- " << elev << endl;
            // waitKey(1);
            outputVideo.write(src); //save or


        }
    }
}

void videorw::getturretimgdata(uchar *data,int rows, int cols, int dim,float azi , float elev, bool recordingEnable)
{

    if(recordingEnable)
    {
        Mat src = cv::Mat(rows,cols,CV_8UC3);


        if (data)
        {
            memcpy(src.data, data, rows * cols * 3);
            outputVideo.write(src);
            cout << "image received and image written" << endl;
        }
        else
        {
            cout << "NULL" << endl;
        }
    }
    else
    {

        cout << "image received and not written" << endl;
    }


}
