#ifndef DIRECTIONVECTOR_H
#define DIRECTIONVECTOR_H

#include "opencv2/opencv.hpp"
#include "params.h"

using namespace cv;
using namespace std;
/*
*	边界编号
    UPANDLEFT						UP							UPANDRIGHT
        ----------------------------------------------------------------------->+x
        |															|
        |															|
        |															|
        |															|
        |															|
        |															|
        |															|
        |															|
        |															|
    LEFT|															|RIGHT
        |															|
        |															|
        |															|
        |															|
        |															|
        |															|
        |-----------------------------------------------------------|
    DOWNANDLEFT						DOWN						DOWNANDRIGHT
        |+y
*/
/* 边界处理类 */
class DirectionVector
{
public:
    DirectionVector();
    DirectionVector(Point2f ptStart, Point2f ptEnd);
    float GetEdgeAngle();

    Point2f ptStart;
    Point2f ptEnd;
    Point2f ptVector;

    float CalculateEdgeAngle(bool);
private:
    void GetEdgeType();
    bool GetIntersection(int x0,int y0);//0:up or down;1:left or right

    float GetAngle(Point2f pt0,Point2f pt1,Point2f pt);
    float GetDistance(Point2f pt0,Point2f pt1);
    float GetSquare(Point2f pt0,Point2f pt1,Point2f pt);
    enum EdgeType edge;
};

#endif // DIRECTIONVECTOR_H
