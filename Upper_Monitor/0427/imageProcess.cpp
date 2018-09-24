#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * *对每帧图像进行分析处理
 */
void MainWindow::GetFrame()
{
    //读入原图,灰度化并进行阈值分割
    timer->stop();

    //获取原图并预处理
    Capture >> Frame;
    cvtColor(Frame,FrameGray,CV_BGR2GRAY);
    blur(FrameGray,FrameGray,Size(BlurSize,BlurSize));
    threshold(FrameGray, FrameBinary, ThreVal, 255, THRESH_BINARY);
    FrameResized = Cc.ccRemap(FrameBinary);

    //Blob分析及运算
    AnalyzeImage();

    //串口发送
    SendAngleAndDistanceData(DirAngle, Angle, Distance);
    qDebug("DirAngle:%d",DirAngle);
    qDebug("Angle:%d",Angle);
    qDebug("Distance:%d",Distance);

    //在原彩色图上画出三个连通域（此操作会使帧率下降8-10帧）
    //DrawnOnFrame();
    ShowImage();

    timer->start();
}

/*
 ** Blob获取轮廓
 */
bool MainWindow::GetContours(Mat &mat)
{
    Pt2DContours.clear();
    ContourResults.clear();
    Hierarchy.clear();

    findContours(mat.clone(), Pt2DContours, Hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //cout << "get " << Pt2DContours.size() << " contours" << endl;

    //面积阈值分割，获取较大面积的轮廓
    for(unsigned int num = 0;num < Pt2DContours.size();num++)
    {
        Contour tempContour;
        tempContour.m_Area = contourArea(Pt2DContours[num]);
        if(tempContour.m_Area > MinBlobArea)
        {
            Moments mu = moments(Pt2DContours[num],false);
            tempContour.m_PtCentroid = Point2f( mu.m10/mu.m00 , mu.m01/mu.m00 );
            ContourResults.push_back(tempContour);
        }
    }
    //cout << "after: get " << ContourResults.size() << " contours" << endl;


    //获取的Blob数量小于3个则返回false
    if(ContourResults.size()<3 )return false;

    //否则确定3个Blob中谁是信标、车头和车尾
    //cout<<"get three points"<<endl;
    return GetCentroid();
}

/*
 * *获取信标、车头、车尾的坐标点
 * *目前： 面积最大为车尾，面积次之为信标（距离最远），面积最小为车头
 */
bool MainWindow::GetCentroid()
{
    // 按照轮廓面积由大到小排序
    for(unsigned int i=0;i<ContourResults.size();i++)
    {
        for(unsigned int j=0;j<ContourResults.size()-i-1;j++)
        {
            if(ContourResults[j].m_Area<ContourResults[j+1].m_Area)
            {
                Contour tmp = ContourResults[j];
                ContourResults[j] = ContourResults[j+1];
                ContourResults[j+1] = tmp;
            }
        }
    }

    float vec1to2_len,vec1to3_len,vec2to3_len;

    vec1to2_len = GetDistance(ContourResults[0].m_PtCentroid,ContourResults[1].m_PtCentroid);
    vec1to3_len = GetDistance(ContourResults[0].m_PtCentroid,ContourResults[2].m_PtCentroid);
    vec2to3_len = GetDistance(ContourResults[1].m_PtCentroid,ContourResults[2].m_PtCentroid);

    //最远的是信标灯，剩下面积最大的是车尾
    if((vec1to2_len<vec1to3_len)&&(vec1to2_len<vec2to3_len))
    {
        PtBeacon = ContourResults[2].m_PtCentroid;

        PtCarMid = ContourResults[0].m_PtCentroid;
        PtCarFront = ContourResults[1].m_PtCentroid;

        Distance = (short)vec2to3_len;
    }
    else if((vec1to3_len<vec1to2_len)&&(vec1to3_len<vec2to3_len))
    {
        PtBeacon = ContourResults[1].m_PtCentroid;

        PtCarMid = ContourResults[0].m_PtCentroid;
        PtCarFront = ContourResults[2].m_PtCentroid;

        Distance = (short)vec2to3_len;
    }
    else if((vec2to3_len<vec1to2_len)&&(vec2to3_len<vec1to3_len))
    {
        PtBeacon = ContourResults[0].m_PtCentroid;

        PtCarMid = ContourResults[1].m_PtCentroid;
        PtCarFront = ContourResults[2].m_PtCentroid;

        Distance = (short)vec1to3_len;
    }
    //else???

    return true;
}

/*
 * *在界面上画出三个Blob
 * *红->信标，绿->车尾，蓝->车头
 */
void MainWindow::DrawnOnFrame()
{
#ifdef SHOW_UI
    if(PtBeacon!=Point2f(-1,-1))
        circle(Frame,PtBeacon,3,Scalar(0,0,255),-1);
    if(PtCarMid!=Point2f(-1,-1))
        circle(Frame,PtCarMid,3,Scalar(0,255,0),-1);
    if(PtCarFront!=Point2f(-1,-1))
        circle(Frame,PtCarFront,3,Scalar(255,0,0),-1);
#endif
}

/*
 * *在界面上显示图像
*/
void MainWindow::ShowImage()
{
#ifdef SHOW_UI
    QImage image;
    Mat Frame_RGB = Mat::zeros(Size(CAPTURE_WIDTH,CAPTURE_HEIGHT),CV_8UC3);
    Mat Frame_temp = Mat::zeros(Size(CAPTURE_WIDTH,CAPTURE_HEIGHT),CV_8UC1);

    //显示原图会使帧率掉4帧
    //-------------------------------------------------- 原始图 --------------------------------------------------
    cvtColor(Frame,Frame_RGB,CV_BGR2RGB);
    image = QImage((const uchar*)(Frame_RGB.data), Frame_RGB.cols,Frame_RGB.rows,Frame_RGB.cols*Frame_RGB.channels(),QImage::Format_RGB888).scaled(ui->label_Frame->width(),ui->label_Frame->height());
    ui->label_Frame->setPixmap(QPixmap::fromImage(image));
    //-------------------------------------------------- 灰度图 --------------------------------------------------
    cv::resize(FrameGray,Frame_temp,Size(ui->label_Frame_gray->width(), ui->label_Frame_gray->height()));
    image = QImage((const uchar*)(Frame_temp.data),Frame_temp.cols,Frame_temp.rows,Frame_temp.cols*Frame_temp.channels(),QImage::Format_Indexed8);
    ui->label_Frame_gray->setPixmap(QPixmap::fromImage(image));
    //-------------------------------------------------- 二值化 --------------------------------------------------
    cv::resize(FrameBinary,Frame_temp,Size(ui->label_Frame_binary->width(), ui->label_Frame_binary->height()));
    image = QImage((const uchar*)(Frame_temp.data),Frame_temp.cols,Frame_temp.rows,Frame_temp.cols*Frame_temp.channels(),QImage::Format_Indexed8);
    ui->label_Frame_binary->setPixmap(QPixmap::fromImage(image));
    //-------------------------------------------------- 矫正图 --------------------------------------------------
    //cvtColor(FrameResized,Frame_RGB,CV_BGR2RGB);
    //image = QImage((const uchar*)(Frame_RGB.data),Frame_RGB.cols,Frame_RGB.rows,Frame_RGB.cols*Frame_RGB.channels(),QImage::Format_RGB888).scaled(ui->label_Frame_resized->width(),ui->label_Frame_resized->height());
    //ui->label_Frame_resized->setPixmap(QPixmap::fromImage(image));
    cv::resize(FrameResized,Frame_temp,Size(ui->label_Frame_resized->width(), ui->label_Frame_resized->height()));
    image = QImage((const uchar*)(Frame_temp.data),Frame_temp.cols,Frame_temp.rows,Frame_temp.cols*Frame_temp.channels(),QImage::Format_Indexed8);
    ui->label_Frame_resized->setPixmap(QPixmap::fromImage(image));
#endif

#ifdef SHOW_UI_HELPER
    ui->lineEdit_Distance->setText(QString::number(Distance,10));
#endif
}

/*
 * *(原来，现暂时不用)Blob获取轮廓
 */
bool MainWindow::GetContours()
{
    Pt2DContours.clear();
    ContourResults.clear();
    Hierarchy.clear();

    findContours(FrameBinary.clone(), Pt2DContours, Hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //    findContours(FrameBinary, Pt2DContours, Hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    //面积阈值分割，获取较大面积的轮廓
    for(unsigned int num = 0;num < Pt2DContours.size();num++)
    {
        Contour tempContour;
        tempContour.m_Area = contourArea(Pt2DContours[num]);
        if(tempContour.m_Area > MinBlobArea)
        {
            Moments mu = moments(Pt2DContours[num],false);
            tempContour.m_PtCentroid = Point2f( mu.m10/mu.m00 , mu.m01/mu.m00 );
            ContourResults.push_back(tempContour);
        }
    }

    if(PtCarMid!=Point2f(-1,-1) && PtCarFront!=Point2f(-1,-1))
    {
        EdgeHelper = new DirectionVector(PtCarMid,PtCarFront);
        //cout<<"PTSTART.X:"<<DV->ptStart.x<<endl;
    }
    PtBeacon = PtCarFront = PtCarMid = Point2f(-1,-1);
    Distance = 0;

    //获取的Blob数量小于3个则返回
    if(ContourResults.size()<3 )  return false;

    return GetCentroid();
}
