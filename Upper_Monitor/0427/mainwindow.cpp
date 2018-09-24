#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化全局变量和界面
    InitParams();
    InitRemap();
    InitUI();
}

MainWindow::~MainWindow()
{
    if (serial.isOpen())
        serial.close();
    if (Capture.isOpened())
    {
        timer->stop();
        Capture.release();
    }

    delete timer;
    delete ui;
}

/*
 * *初始化全局参数
*/
void MainWindow::InitParams()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(GetFrame()));

    PtBeacon = PtCarMid = PtCarFront = Point2f(-1, -1);
    BlurSize = 2;
    ThreVal = 100;
    MinBlobArea = 0;
    Angle = 0;
    Distance = 0;
    //0：右转 1：左转
    DirAngle = 0;
    IsInView = 0;
}

/* 初始化界面显示 */
void MainWindow::InitUI()
{
#ifdef SHOW_UI
    ui->lineEdit_ThreVal->setText(QString(QString::number(ThreVal, 10)));
    ui->lineEdit_BlurSize->setText(QString(QString::number(BlurSize, 10)));
    ui->lineEdit_AreaMin->setText(QString("%1").arg(MinBlobArea));
#endif
}

/*
 * *初始化畸变矫正参数
 */
void MainWindow::InitRemap()
{
    Mat camerMatirx,disCoeffs;

#ifdef WINDOWS_PLATFORM
    FileStorage camerMatirxFS("C:\\Users\\Administrator\\Desktop\\Graduation_Project\\Upper_Monitor\\CalibrateDatas\\camerMatirx.xml", FileStorage::READ);
    FileStorage disCoeffsFS("C:\\Users\\Administrator\\Desktop\\Graduation_Project\\Upper_Monitor\\CalibrateDatas\\disCoeffs.xml", FileStorage::READ);
#else
    FileStorage camerMatirxFS("/home/pi/Desktop/FourShaft/0427/camerMatirx.xml", FileStorage::READ);
    FileStorage disCoeffsFS("/home/pi/Desktop/FourShaft/0427/disCoeffs.xml", FileStorage::READ);
#endif

    camerMatirxFS["camerMatirx"] >> camerMatirx;
    disCoeffsFS["disCoeffs"] >>disCoeffs;
    camerMatirxFS.release();
    disCoeffsFS.release();

    Cc.inputMaxtrix(camerMatirx, disCoeffs);
}

/*
**捕获照片
*/
void MainWindow::on_pushButton_TakePhoto_clicked()
{
    static int fileCnt=0;
    std::string fileFolder = "C:\\Users\\Administrator\\Desktop\\Graduation_Project\\Upper_Monitor\\CalibrateImages";
    std::string fileName = "chessboard";

    Capture >> Frame;

    stringstream s;
    s << fileFolder << '/' << fileName << setw(2) << setfill('0') << fileCnt++ << ".jpg";

    imwrite(s.str(), Frame);
}

/*
 * * 标定按钮
*/
void MainWindow::on_pushButton_Calibrate_clicked()
{
    vector<string> fileList;
    string fileFolder = "C:\\Users\\Administrator\\Desktop\\Graduation_Project\\Upper_Monitor\\CalibrateImages";
    string fileName = "chessboard";
    int    fileCount = 9;

    Size boardSize(10, 7);

    cout<<"Start to load images"<<endl;
    for (int i = 0; i <= fileCount; i++)
    {
        stringstream s;
        s << fileFolder << '/' << fileName << setw(2) << setfill('0') << i << ".jpg";

        fileList.push_back(s.str());
        cout<<"Image "<<i <<" has been loaded"<<endl;
        waitKey(50);
    }

    Cc.addChessboardPoints(fileList, boardSize);
    Cc.calibrate();

#if 0
    //保存参数
    FileStorage camerMatirxFS("C:\\Users\\Administrator\\Desktop\\Graduation_Project\\Upper_Monitor\\CalibrateDatas\\camerMatirx.xml", 1);
    FileStorage disCoeffsFS("C:\\Users\\Administrator\\Desktop\\Graduation_Project\\Upper_Monitor\\CalibrateDatas\\disCoeffs.xml", 1);
    Mat camerMatirx = Cc.getCameraMatrix();
    Mat disCoeffs = Cc.getDistCoeffs();
    camerMatirxFS << "camerMatirx" << camerMatirx;
    disCoeffsFS << "disCoeffs" << disCoeffs;
    camerMatirxFS.release();
    disCoeffsFS.release();
#endif
}

/*
 * *打开摄像头按钮
 */
void MainWindow::on_pushButton_OpenCam_clicked()
{
    OpenCamera();
}

/*
** 从界面获取阈值
*/
void MainWindow::on_lineEdit_ThreVal_textChanged(const QString &arg1)
{
    ThreVal = arg1.toInt();
}

/*
 * * 从界面获取滤波块大小
 */
void MainWindow::on_lineEdit_BlurSize_textChanged(const QString &arg1)
{
    BlurSize = arg1.toInt();
}

/*
**从界面获取Blob过滤面积大小
 */
void MainWindow::on_lineEdit_AreaMin_textChanged(const QString &arg1)
{
    MinBlobArea = arg1.toFloat();
}

/*
 * *打开串口按钮
*/
void MainWindow::on_pushButton_OpenPort_clicked()
{
    OpenSerialPort();
}

/*
 * * 打开串口
 */
void MainWindow::OpenSerialPort()
{
    if(!serial.isOpen())
    {
        InitSerialPort();
        serial.close();

        if(serial.open(QIODevice::ReadWrite))
        {
            connect(&serial,SIGNAL(readyRead()),this,SLOT(ReadCom()));
            if(serial.isOpen())
            {
                ui->pushButton_OpenPort->setText("关闭串口");
                ui->comboBox_SerialPort->setDisabled(true);
            }
        }
    }
    else
    {
        serial.close();
        ui->pushButton_OpenPort->setText("打开串口");
        ui->comboBox_SerialPort->setDisabled(false);
    }
}

/*
 * *打开摄像头
*/
void MainWindow::OpenCamera()
{
    if (!Capture.isOpened())
    {
        Capture.open(ui->comboBox_CameraPath->currentText().toInt());

        Capture.set(CV_CAP_PROP_FRAME_WIDTH, CAPTURE_WIDTH);
        Capture.set(CV_CAP_PROP_FRAME_HEIGHT, CAPTURE_HEIGHT);
        //Capture.set(CV_CAP_PROP_FOURCC,CV_FOURCC('M', 'J', 'P', 'G'));//28    1196444237
        //Capture.set(CV_CAP_PROP_FOURCC,CV_FOURCC('L', 'C', 'W', '2'));//30    844579660
        //Capture.set(CV_CAP_PROP_FOURCC,CV_FOURCC('L', 'J', '2', 'K'));//28    1261587020
        //Capture.set(CV_CAP_PROP_FOURCC,CV_FOURCC('L', 'J', 'P', 'G'));//28    1196444236
        //Capture.set(CV_CAP_PROP_FOURCC,CV_FOURCC('M', 'J', '2', 'C'));//27    1127369293
        //Capture.set(CV_CAP_PROP_FOURCC,1196444237.000000);
        //Capture.set(CV_CAP_PROP_FOURCC,CV_FOURCC('X', '2', '6', '4'));//30    875967064

        if (Capture.isOpened())
        {
            timer->start(30);
            ui->pushButton_OpenCam->setText("关闭相机");
        }
    }
    else
    {
        timer->stop();
        Capture.release();
        ui->pushButton_OpenCam->setText("打开相机");
    }
}
