#ifndef __EAGLECAMERA_H
#define __EAGLECAMERA_H

#include "common.h"
#include "include.h"

#include "control.h"
#include "encoder.h"
#include "motor.h"
#include "Imageprocessing.h"

#include "VCAN_camera.h"      
#include "VCAN_OV7725_Eagle.h"
#include "VCAN_SCCB.h"

extern uint8 imgbuff[OV7725_EAGLE_SIZE];
extern uint8 u8_EagleImgBuffer[OV7725_EAGLE_H][OV7725_EAGLE_W];   // 60x160  Storage camera data

void EagleCameraInit();
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void GetImg(void *img);

#endif