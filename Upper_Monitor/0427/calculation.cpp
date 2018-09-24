#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * *得到两点距离
 */
float MainWindow::GetDistance(Point2f &pt1,Point2f &pt2)
{
    float deltaX = pt1.x - pt2.x;
    float deltaY = pt1.y - pt2.y;

    deltaY = deltaY*HV_RATIO;
    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

/*
 * * 得到角度的正负
 */
float MainWindow::GetSquare(Point2f &pt1, Point2f &pt2, Point2f &pt3)
{
    return (pt1.x-pt3.x)*(pt2.y-pt3.y)-(pt1.y-pt3.y)*(pt2.x-pt3.x);
}

/*
* * 得到信标灯、车头、车尾构成三角形的角度
 */
void MainWindow::GetAngle()
{
    float vec1to2_len,vec1to3_len,vec2to3_len;

    vec1to2_len = GetDistance(PtCarMid,PtCarFront);
    vec1to3_len = GetDistance(PtCarMid,PtBeacon);
    vec2to3_len = GetDistance(PtCarFront,PtBeacon);

    float cosval = (vec1to2_len*vec1to2_len+vec1to3_len*vec1to3_len-vec2to3_len*vec2to3_len)/
            (2*vec1to2_len*vec1to3_len);

    float square = GetSquare(PtCarMid,PtCarFront,PtBeacon);
    DirAngle = (square>0)?0:1;


    Angle = acos(cosval)*180/CV_PI;

#ifdef SHOW_UI_HELPER
    QString dirStr = QString::number(DirAngle,10)==0?"Right":"Left";
    ui->lineEdit_DirAngle->setText(dirStr);
    ui->lineEdit_Angle->setText(QString::number(Angle,10));
#endif

#ifdef SHOW_DEBUG
    qDebug("angle:%d",Angle);
    qDebug("a: %f, b: %f c:%f",vec1to2_len,vec1to3_len,vec2to3_len);
    qDebug("Get three point: Direction: %d angle:%d",DirAngle,Angle);
#endif
}
