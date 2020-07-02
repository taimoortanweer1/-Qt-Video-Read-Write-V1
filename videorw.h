#ifndef VIDEORW_H
#define VIDEORW_H

#include <QObject>
#include <QPixmap>
#include <thread>
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat)
#include <opencv2/videoio.hpp>  // Video write
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class videorw : public QObject {
    Q_OBJECT
public:
    explicit videorw(QObject *parent = nullptr);
             videorw(VideoCapture *vcap, cv::String deststr);

signals:

public slots:
    void getturretimg(float azi,float elev, Mat Img, bool enable);
    //void getturretimg(Mat Img);
    //void getturretimgQ(float azi,float elev, QPixmap Img, bool enable);
    void getturretimgQ(float azi,float elev, QImage Img, bool enable);
    void getturretimgdata(uchar *data,int rows, int cols, int dim,float azi , float elev, bool recordingEnable);
private:
    VideoCapture *inputVideo;
    VideoWriter  *vwrite;
    VideoWriter outputVideo;
    cv::String destString;
    Size sizeOfVideo;
    int codec;
    bool endFlag;
    Mat Frame;
    QPixmap QFrame;
    bool start;
};

#endif // VIDEORW_H
