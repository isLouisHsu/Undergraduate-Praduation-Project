#ifndef __CONTROL_H
#define __CONTROL_H

#include "common.h"
#include "include.h"
#include "eaglecamera.h"
#include "encoder.h"
#include "LedKey.h"
#include "bluetooth.h"

extern uint32 g_iSteeringValue;
extern uint32 g_iSteeringMid;
extern uint32 g_iSteeringLeft;
extern uint32 g_iSteeringRight ;
extern uint32 g_iSteeringLeftRange;
extern uint32 g_iSteeringRightRange;
extern uint32 g_iSteeringAdd;

extern float g_fSteeringP;
extern float g_fSteeringI;
extern float g_fSteeringD;

extern float g_fSteeringCoefficientP1;
extern float g_fSteeringCoefficientP2;
extern float g_fSteeringCoefficientP3;
extern float g_fSteeringCoefficientP4;
extern float g_fSteeringCoefficientD1;
extern float g_fSteeringCoefficientD2;
extern float g_fSteeringCoefficientD3;
extern float g_fSteeringCoefficientD4;

extern float g_fSpeedP;
extern float g_fSpeedI;
extern float g_fSpeedD;
extern uint32 g_u32SpeedP ;
extern uint32 g_u32SpeedI ;
extern uint32 g_u32SpeedD ;
extern float g_fSpeedP1;
extern float g_fSpeedI1;
extern float g_fSpeedD1;

extern int  g_iSpeedSet;
extern int g_iSpeed;
extern int g_iSpeedL;
extern int g_iSpeedR;
extern int g_iSpeedInsideBack;
extern int g_iSpeedOutsideBack;
extern int g_iSpeedInside;
extern int g_iSpeedOutside;
extern int g_iSpeedVaule;
extern int g_iSpeedVauleL;
extern int g_iSpeedVauleR;

extern uint8 g_u8TurnDir[20];
extern uint8 g_u8TopL[20];
extern uint8 g_u8TopR[20];
extern uint16 g_iDistanceNear;
extern uint16 g_iDistanceFar;
extern int g_iNear ;
extern int g_iFar;
extern int g_iCount ;
extern int g_iAccelerate ;
extern int g_iLightCheck;
extern int g_iFlagTurn;
extern int g_iFlagBack;
extern int g_iTurnMsCnt;
extern int g_iBackMsCnt;

extern int g_iSpeedSetAverage;
extern uint8 g_u8MovingSta;

void MovingStateJudge(void);
void BeaconCounter(void);

void CoreControl(void);
void CoreControlC(void);

void AddSteerError();
void AddSteerOutError(void);

void SteeringPID(void);
void MotorPID(int speed_parameter1,int speed_parameter2);
void SpeedRelateToSteer(void);

#endif 