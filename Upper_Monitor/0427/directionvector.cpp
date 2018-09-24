#include "directionvector.h"

/* 默认构造函数 */
DirectionVector::DirectionVector()
{
    /* Do Nothing */
}

/*
 * * 用车头和车尾坐标点初始化构造函数
 */
DirectionVector::DirectionVector(Point2f ptStart, Point2f ptEnd)
{
    //保存点坐标
    this->ptStart   = ptStart;
    this->ptEnd     = ptEnd;
    this->ptVector  = ptEnd - ptStart;
    this->edge      = Edge_InvalidStart;
}

/*
 * *计算车是从哪个边缘出去的
 */
void DirectionVector::GetEdgeType()
{
    if((ptVector.x==0)&&(ptVector.y<0))
        edge = Edge_Up;
    else if((ptVector.x==0)&&(ptVector.y>0))
        edge = Edge_Down;
    else if((ptVector.x<0)&&(ptVector.y==0))
        edge = Edge_Left;
    else if((ptVector.x>0)&&(ptVector.y==0))
        edge = Edge_Right;
    else if((ptVector.x<0)&&(ptVector.y<0))
        edge = Edge_UpLeft;
    else if((ptVector.x>0)&&(ptVector.y<0))
        edge = Edge_UpRight;
    else if((ptVector.x<0)&&(ptVector.y>0))
        edge = Edge_DownLeft;
    else if((ptVector.x>0)&&(ptVector.y>0))
        edge = Edge_DownRight;
    else
        edge=Edge_InvalidStart;
}

/*
 * *计算车姿方向与边界的交点
 * *0:up or down
 * *1:left or right
 */
bool DirectionVector::GetIntersection(int x0,int y0)
{
    float k = ptVector.y/ptVector.x;
    float b = ptEnd.y - k*ptEnd.x;

    float yInter=k*x0+b;
    float xInter=(y0-b)/k;

    //cout<<"x and y"<<xInter<<","<<yInter<<endl;

    if(yInter>=0&&yInter<=240)
        return true;
    else if(xInter>=0&&xInter<=320)
        return false;
}

float DirectionVector::CalculateEdgeAngle(bool isHorizenOrVertical)
{
    Point2f ptEdge = isHorizenOrVertical?Point2f(0,ptVector.y):Point2f(ptVector.x,0);
    float angle =GetAngle(Point(0,0),ptVector,ptEdge);
    //cout<<"angle:"<<angle<<endl;
    return angle;
}

/*
 * * 得到最终的边缘舵机角度
*/
float DirectionVector::GetEdgeAngle()
{
    float angle=0;

    GetEdgeType();
    switch(edge)
    {
    case Edge_Up:
        angle=90;break;
    case Edge_Down:
        angle=90;break;
    case Edge_Left:
        angle=90;break;
    case Edge_Right:
        angle=90;break;
    case Edge_UpLeft:
        angle = CalculateEdgeAngle(GetIntersection(0,0));
        break;
    case Edge_UpRight:
        angle = CalculateEdgeAngle(GetIntersection(CAPTURE_WIDTH,0));
        break;
    case Edge_DownLeft:
        angle = CalculateEdgeAngle(GetIntersection(0,CAPTURE_HEIGHT));
        break;
    case Edge_DownRight:
        angle = CalculateEdgeAngle(GetIntersection(CAPTURE_WIDTH,CAPTURE_HEIGHT));
        break;
    default:break;
    }
    return angle;
}

float DirectionVector::GetAngle(Point2f pt0, Point2f pt1, Point2f pt)
{
    float lenPt0ToPt1,lenPt0ToPt,lenPt1ToPt;

    lenPt0ToPt1 = GetDistance(pt0,pt1);
    lenPt0ToPt  = GetDistance(pt0,pt);
    lenPt1ToPt  = GetDistance(pt1,pt);
    //    qDebug("a: %f, b: %f c:%f",lenPt0ToPt1,lenPt0ToPt,lenPt1ToPt);
    //    qDebug("Get three point: Direction: %d angle:%d",DirAngle,Angle);

    float cosval = (lenPt0ToPt1*lenPt0ToPt1+lenPt0ToPt*lenPt0ToPt-lenPt1ToPt*lenPt1ToPt)/
            (2*lenPt0ToPt1*lenPt0ToPt);

    float square = GetSquare(pt0,pt1,pt);
    if(square>0)//right
        return acos(cosval)*180/CV_PI;
    else
        return -acos(cosval)*180/CV_PI;
}

float DirectionVector::GetDistance(Point2f pt0, Point2f pt1)
{
    float deltaX = pt0.x - pt1.x;
    float deltaY = pt0.y - pt1.y;

    deltaY = deltaY*HV_RATIO;
    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

float DirectionVector::GetSquare(Point2f pt0, Point2f pt1, Point2f pt)
{
    return (pt0.x-pt.x)*(pt1.y-pt.y)-(pt0.y-pt.y)*(pt1.x-pt.x);
}
