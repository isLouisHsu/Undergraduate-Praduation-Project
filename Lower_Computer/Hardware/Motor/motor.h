#ifndef __MOTOR_H
#define __MOTOR_H

#include "common.h"
#include "include.h"

#define MOTOR_FTM FTM0				//motor ftm :ftm0Here is fixed FTM0, if you want to modify, please remember to modify here!!
#define MOTOR_FTM_PASS_1   FTM_CH4	//motor ftm pass:ftm0_ch4~7  Here is fixed FTM0_CH4~7, if you want to modify, please remember to modify here!!	
#define MOTOR_FTM_PASS_2   FTM_CH5
#define MOTOR_FTM_PASS_3   FTM_CH6
#define MOTOR_FTM_PASS_4   FTM_CH7

extern FTM_MemMapPtr FTMN[3];

void MotorInit(uint32 freq);		//motor init
void motor1(uint32 duty);
void motor2(uint32 duty);
void motor3(uint32 duty);
void motor4(uint32 duty);
void CMotorDrive(int speed1,int speed2);			//C car motor drive
void BMotorDrive(int speed);		//B car motor drive

#endif