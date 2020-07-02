#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videorw.h"
#include <QImage>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    videorw *vi;
    VideoCapture *vc;
    bool getImagesFlag;
    std::thread *t_cap;
    Mat frame;
    QPixmap Qframe;
    QImage Qimg;
    bool recordingEnable;


public:

signals:
    void setturretimg(float azi,float elev, Mat Img, bool enable);
    //void setturretimgQ(float azi,float elev, QPixmap QImg, bool enable);
    void setturretimgQ(float azi,float elev, QImage QImg, bool enable);
    void displayturretimg(QPixmap QImg);
    void sendturretimgdata(uchar *data,int rows, int cols, int dim, float azi , float elev, bool recordingEnable);

private slots:
    void on_pushButton_clicked();
    void videoGetSet();
    void on_checkBox_toggled(bool checked);
};

#endif // MAINWINDOW_H
