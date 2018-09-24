#ifndef __ENCODER_H
#define __ENCODER_H

#include "common.h"
#include "include.h"

#include "LedKey.h"

#define COUNTER1_FTM	FTM1
#define COUNTER1_A		PTA13
#define COUNTER1_B		PTA12

extern int16 g_i16LeftVal,g_i16RightVal,g_i16LastLeftVal,g_i16LastRightVal;
extern int g_iAverageSpeed,g_iLastAverageSpeed;
extern int g_iFlagCount1 ;
extern int g_iFlagStable ;
extern int g_iProtectMotor;
extern int g_iProtectFlag;
extern int g_iStopMotor;
extern int g_iStableGrade15;
extern int g_iStableGrade45;
extern int g_iStableGrade75;
extern int g_iStableGrade105;

extern  int g_iStableGrade275;
extern  int g_iVCount275;
extern  int g_iStableGrade325;
extern  int g_iVCount325;
extern  int g_iStableGrade375;
extern  int g_iVCount375;
extern  int g_iStableGrade425;
extern  int g_iVCount425;
extern  int g_iStableGrade475;
extern  int g_iVCount475;

extern int g_iVCount1;
extern int g_iVCount2;
extern int g_iVCount3;
extern int g_iVCount4;

extern int g_iSpeedError ;


void EncoderInit(void);
void BVelocityMeasurement(void);
void CVelocityMeasurement(void);
void DMA_CH2_Handler(void);
void AverageSpeedCalculation(void);

#endif 