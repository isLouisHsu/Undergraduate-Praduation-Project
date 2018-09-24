#ifndef PARAMS_H
#define PARAMS_H

#include "mainwindow.h"

typedef unsigned short  ushort;
typedef unsigned char   uchar;

//#define SHOW_DEBUG             //编译开关：显示Debug信息
#define SHOW_UI                //编译开关：在界面上显示信息
//#define SHOW_UI_HELPER         //编译开关：界面上是否显示辅助信息
#define WINDOWS_PLATFORM

#define HV_RATIO            (62.2778/83.1)//(3/4)
#define CAPTURE_WIDTH       320 //摄像头捕获分辨率：长
#define CAPTURE_HEIGHT      240 //摄像头捕获分辨率：宽

//添加边界枚举定义，八个方向
enum EdgeType
{
    Edge_InvalidStart   = 0,
    Edge_Start          = 1,
    Edge_Up             = 1,
    Edge_Down           = 2,
    Edge_Left           = 3,
    Edge_Right          = 4,
    Edge_UpLeft         = 5,
    Edge_UpRight        = 6,
    Edge_DownLeft       = 7,
    Edge_DownRight      = 8,
    Edge_End            = 8
};

#endif // PARAMS_H
