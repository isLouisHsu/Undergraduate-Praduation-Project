#ifndef __LEDKEY_H
#define __LEDKEY_H

#include "common.h"
#include "include.h"
#include "eaglecamera.h"
#include "oled.h"
#include "steering.h"
#include "control.h"
#include "encoder.h"
#include "Imageprocessing.h"

extern uint8 switch_sta;
extern int g_iThreshold;
extern int g_ichoice;
extern int g_ichoiceShow;
extern int g_ichoiceMotor;
extern int g_ichoiceSteer;
extern int g_iKeyValue;
//extern uint8 u8_EagleImgBuffer[LINE][COLUMN];

uint8 Switch();
void IoLedKeyDialInit(void);
//void Oled_Show_Camera(uint8 *camera_arry,uint8 width,uint8 height);
void OledShow(void);
void LedControl(int x);
void KeyScan(void);
void TopLParameterAdjustment();

#endif 