#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QSerialPort>
#include <vector>
#include <math.h>
#include <iomanip>
#include "directionvector.h"
#include "contour.h"
#include "cameracalibrate.h"

using namespace cv;
using namespace std;

class DirectionVector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void OpenCamera();
    void OpenSerialPort();

    DirectionVector *EdgeHelper;

private slots:
    void GetFrame();
    void ReadCom();

    void on_pushButton_OpenCam_clicked();
    void on_pushButton_TakePhoto_clicked();
    void on_pushButton_OpenPort_clicked();
    void on_pushButton_Calibrate_clicked();

    void on_lineEdit_ThreVal_textChanged(const QString &arg1);
    void on_lineEdit_BlurSize_textChanged(const QString &arg1);
    void on_lineEdit_AreaMin_textChanged(const QString &arg1);

private:
    void InitParams();
    void InitUI();

    void DrawnOnFrame();
    void ShowImage();

    bool GetContours();
    bool GetContours(Mat &mat);
    bool GetCentroid();

    /******************** 摄像头标定 *********************/
    CameraCalibrate Cc;
    Mat cameraMatrix;
    Mat distCoeffs;
    Mat map1, map2;
    void InitRemap();

    /******************* 图像分析 *********************/
    void AnalyzeImage();

    /************** 计算角度、距离等 ***************/
    float GetDistance(Point2f &pt1, Point2f &pt2);
    float GetSquare(Point2f &pt1, Point2f &pt2, Point2f &pt3);
    void GetAngle();

    /************** 串口相关 ***************/
    void InitSerialPort();
    void SendControlData(char dirAngle,char angle,char reserved,char dirSpeed,ushort speed);
    void SendAngleAndDistanceData(char dirAngle, char angle, ushort distance);

    Ui::MainWindow *ui;
    QTimer *timer;
    QSerialPort serial;

    //摄像头图像
    VideoCapture Capture;
    Mat Frame,FrameResized,FrameGray,FrameBinary;

    //滤波,灰度阈值,面积阈值大小
    int BlurSize;
    int ThreVal;
    float MinBlobArea;

    //电机控制参数
    char Angle;
    ushort Distance;
    //0:右,1:左
    char DirAngle;
    char IsInView;

    //检测到的轮廓
    vector<vector<Point> > Pt2DContours;
    //各个轮廓的继承关系
    vector<Vec4i> Hierarchy;
    vector<Contour> ContourResults;

    /************** 三个连通域位置坐标 **************/
    Point2f PtBeacon,PtCarMid,PtCarFront;
};

#endif // MAINWINDOW_H
