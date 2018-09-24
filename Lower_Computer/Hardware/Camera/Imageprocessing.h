#ifndef __IMAGEPROCESSING_H
#define __IMAGEPROCESSING_H

#include "common.h"
#include "include.h"
#include "eaglecamera.h"
#include "predatorcamera.h"

#define LINE 	60		//max line 
#define COLUMN 	160		//max column

#define BLACK1  0     	//balck
#define WHITE1  1     	//wihte
#define BLACK   0     	//balck
#define WHITE   255   	//wihte

extern int g_iJudege;      //g_iJudege=1:Collecting image ;g_iJudege=0,control
extern int g_iThreshold;
extern int g_iMain; 
extern uint8 g_u8Top;
extern uint8 g_u8LastTop;
extern uint8 g_u8BeaconLocation;
extern uint8 g_u8LastBeaconLocation;
extern uint8 g_u8FindBeacon;
extern float g_fDeviation,g_fLastDeviation,g_fTwoDeviation;

/**********Specific parameter:EagalCameraBeaconHandle2**********/
extern uint8 g_u8FFPoint;             //FindFirstPoint
extern uint8 g_u8FSPoint;             //FindSecondPoint
extern uint8 g_u8LRelCoe;            //LINE Reliability coefficient
extern uint8 g_u8CRelCoe;            //COLUMN Reliability coefficient
extern uint8 g_u8OledShowLX;
extern uint8 g_u8OledShowLY;
extern uint8 g_u8OledShowRX;
extern uint8 g_u8OledShowRY;
extern uint8 g_OledShowPermit;

extern float g_faddimage;
/***************************************************************/
//≤∂ ≥’ﬂ…„œÒÕ∑
void CameraBinaryzation(void);
void PredatorCameraBeaconHandle1(void);
void PredatorCameraBeaconHandle2(void);

//”•—€…„œÒÕ∑
void EagalCameraBeaconHandle1(void);
void EagalCameraBeaconHandle2(void);


#endif
