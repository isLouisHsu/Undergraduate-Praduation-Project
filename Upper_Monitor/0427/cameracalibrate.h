#ifndef CAMERACALIBRATE_H
#define CAMERACALIBRATE_H

#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/* 相机标定类 */
class CameraCalibrate
{
public:
    CameraCalibrate():flag(0), mustInitUndistort(true){}
    //Open files and extract points
    int addChessboardPoints(const vector<string>&filelist, Size &boardSize);
    double calibrate();
    void inputMaxtrix(const Mat cameraMatrix, const Mat distCoeffs);
    Mat ccRemap(const Mat &image);

    Mat getCameraMatrix() const { return cameraMatrix; }
    Mat getDistCoeffs()   const { return distCoeffs; }

private:
    //World cordinate
    vector <vector<Point3f> > objectPoints;
    //Imagination cordinate
    vector <vector<Point2f> > imagePoints;
    //Output matrix
    Mat cameraMatrix;
    Mat distCoeffs;
    Mat map1, map2;
    int flag;
    bool mustInitUndistort;

    void addPoints(const vector<Point2f>&imageCorners, const vector<Point3f>&objectCorners)
    {
        imagePoints.push_back(imageCorners);
        objectPoints.push_back(objectCorners);
    }
};

#endif // CAMERACALIBRATE_H
