#ifndef CONTOUR_H
#define CONTOUR_H

#include <vector>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class Contour
{
public:
    float m_Area;
    Point2f m_PtCentroid;
};

#endif // CONTOUR_H
