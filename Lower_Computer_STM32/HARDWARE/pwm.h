#ifndef __PWM_H

#include "sys.h"

extern int16_t iSpeedSetLeft;
extern int16_t iSpeedSetRight;
extern int16_t iSpeedTurnOutside;
extern int16_t iSpeedTurnInside;
extern int16_t iSpeedLeft;
extern int16_t iSpeedRight;

void TIM2PwmInit(void);
void TIM2PwmOutput(int leftMotor, int rightMotor);

#define __PWM_H
#endif
