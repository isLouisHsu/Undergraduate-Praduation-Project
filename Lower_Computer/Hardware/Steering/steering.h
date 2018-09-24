#ifndef __STEERING_H
#define __STEERING_H

#include "include.h"
#include "common.h"
#include "control.h"

#define STEERING_FTM FTM2		//steeering ftm:fmt2  Here is fixed FTM2, if you want to modify, please remember to modify here!!
#define STEERING_FTM_PASS FTM_CH1	//steering ftm pass:ftm2_ch1  Here is fixed FTM2_CH1, if you want to modify, please remember to modify here!!

extern FTM_MemMapPtr FTMN[3];


void SteeringInit(void);					//steering init
void SteeringPwm(uint32 steering_parameter);	//steering control

#endif  