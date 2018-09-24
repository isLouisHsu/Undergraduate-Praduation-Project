#include "mainwindow.h"
#include "cameracalibrate.h"

void CameraCalibrate::inputMaxtrix(const Mat cameraMatrix, const Mat distCoeffs)
{
    mustInitUndistort = true;

    this->cameraMatrix = cameraMatrix;
    this->distCoeffs = distCoeffs;
}

int CameraCalibrate::addChessboardPoints(const vector<string>&filelist, Size &boardSize)
{
    //Windows平台下暂时有问题，用不到，暂时注释掉
#ifdef WINDOWS_PLATFORM
    return 0;
#else
    vector<Point2f> imageCorners;
    vector<Point3f> objectCorners;
    //input corners in word cordinate
    for (int i=0;i<boardSize.height;i++)
    {
        for (int j=0;j<boardSize.width;j++)
        {
            objectCorners.push_back(Point3f(i, j, 0.0f));
        }
    }
    //calculate the corners in image cordinate
    Mat image;
    int success = 0;
    for (int i=0;i<filelist.size();i++)
    {
        cout << filelist[i] << endl;
        image = imread(filelist[i], 0);
        resize(image, image, Size(CAPTURE_WIDTH, CAPTURE_HEIGHT));
        //find corners
        bool found = findChessboardCorners(image, boardSize, imageCorners);
        cornerSubPix(image, imageCorners, Size(5, 5), Size(-1, -1),
                     TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1));
        if(imageCorners.size() == boardSize.area())
        {
            addPoints(imageCorners, objectCorners);
            success++;
        }
        //draw the corners
        drawChessboardCorners(image,boardSize, imageCorners,found);
        imshow("Corners on chessboard", image);
        waitKey(0);
    }
    return success;
#endif
}

double CameraCalibrate::calibrate()
{
    //Windows平台下暂时有问题，用不到，暂时注释掉
#ifdef WINDOWS_PLATFORM
    return 0;
#else
    mustInitUndistort = true;
    vector<Mat> rvecs, tvecs;

    return calibrateCamera(objectPoints, imagePoints, Size(CAPTURE_WIDTH, CAPTURE_HEIGHT), cameraMatrix, distCoeffs, rvecs, tvecs, flag);
#endif
}

/*
 * *畸变矫正函数
*/
Mat CameraCalibrate::ccRemap(const Mat &image)
{
    Mat undistorted;
    //if (image.size() != Size(CAPTURE_WIDTH, CAPTURE_HEIGHT))return Mat();

    if(mustInitUndistort)
    {
        initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(), Mat(), image.size(), CV_32FC1, map1, map2);
        //参考资料：http://www.cnblogs.com/riddick/p/6711263.html
        //initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
        //getOptimalNewCameraMatrix(cameraMatrix,distCoeffs,image.size(),0), image.size(), CV_16SC2, map1, map2);
        mustInitUndistort = false;
    }

    cv::remap(image, undistorted, map1, map2, INTER_LINEAR);
    return undistorted;
}

