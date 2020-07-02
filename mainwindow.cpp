#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    vc = new VideoCapture("/home/opsroom/Data/SharedVideos/TrackingVideo.mp4");
    vi = new videorw (vc,"/home/opsroom/Data/SharedVideos/test");

    getImagesFlag = false;
    ui->label->setScaledContents(true);
    connect(this,SIGNAL(displayturretimg(QPixmap)),ui->label,SLOT(setPixmap(QPixmap)));

    //connect(this,SIGNAL(setturretimg(float,float,Mat,bool)),vi,SLOT(getturretimg(float,float,Mat,bool)));
    //connect(this,SIGNAL(setturretimgQ(float,float,QPixmap,bool)),vi,SLOT(getturretimgQ(float,float,QPixmap,bool)));
    connect(this,SIGNAL(setturretimgQ(float,float,QImage,bool)),vi,SLOT(getturretimgQ(float,float,QImage,bool)));
    connect(this,SIGNAL(sendturretimgdata(uchar*,int , int , int ,float,float,bool)),vi,SLOT(getturretimgdata(uchar*,int,int,int,float,float,bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(getImagesFlag == false)
    {
        getImagesFlag = true;
        ui->pushButton->setText("Stop Acquiring");
        t_cap = new std::thread;
        *t_cap = std::thread(&MainWindow::videoGetSet,this);

    }
    else
    {

        ui->pushButton->setText("Start Acquiring");
        getImagesFlag = false;

        t_cap->join();
        delete t_cap;

    }
}

void MainWindow::videoGetSet()
{

    while(getImagesFlag == true) //Show the image captured in the window and repeat
    {
        *vc >> this->frame;

        if (this->frame.empty())
            break;
        else
        {

            emit displayturretimg(QPixmap::fromImage( QImage(frame.data, \
                                                             frame.cols, \
                                                             frame.rows, \
                                                             frame.step, \
                                                             QImage::Format_RGB888).rgbSwapped()));
            sendturretimgdata(frame.data,frame.rows,frame.cols,frame.dims,0,0,recordingEnable);

            cout << "frame received" << endl;
        }

        usleep(40000);

    }

    cout << "Quitting" << endl;
}


void MainWindow::on_checkBox_toggled(bool checked)
{
    recordingEnable = checked;
}
