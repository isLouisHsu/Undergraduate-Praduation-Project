#include "mainwindow.h"
#include "ui_mainwindow.h"

/* 图像核心处理程序：
 * *1.矫正后的图像中Blob找三个连通域
 * *2.矫正图上没有，则在原图上寻找
 * *3.原图上没有，则车或信标灯出了图像边界
*/
void MainWindow::AnalyzeImage()
{
    if(GetContours(FrameResized))
    {
        //cout<<"Three points in FrameRemapd"<<endl;
        IsInView = 1;
        GetAngle();                                 //得到角度
    }
    else if(GetContours(FrameBinary))
    {
        //cout<<"Three points in FrameOrigin"<<endl;
        IsInView = 2;
        GetAngle();
    }
    else
    {
        //cout <<"cannot get contours"<<endl;
    }
//    else
//    {
//        //cout<<"Out edge"<<endl;
//        PtBeacon = Point2f(CAPTURE_WIDTH/2,CAPTURE_HEIGHT/2);

//        IsInView = 0;
//        Distance = 1000;

//        float angleTemp = EdgeHelper->GetEdgeAngle();
//        DirAngle = angleTemp<0?1:0;

//        Angle = abs(angleTemp);
//        if(Angle<60) Angle = 60;
//    }
}
