#ifndef __PREDATORCAMERA_H
#define __PREDATORCAMERA_H

#include "common.h"
#include "include.h"
#include "Imageprocessing.h"

#define u8 unsigned char

#define CAM1_Y0			PTE0
#define CAM1_Y1			PTE1
#define CAM1_Y2			PTE2
#define CAM1_Y3			PTE3 
#define CAM1_Y4			PTE4
#define CAM1_Y5			PTE5 
#define CAM1_Y6			PTE6
#define CAM1_Y7			PTE7 
#define CAM1_FODD		PTD15
#define CAM1_PCLK		PTD12		
#define CAM1_HREF		PTD13		
#define CAM1_VSYNC		PTD14	


#define LINE 	60		//max line 
#define COLUMN 	160		//max column


extern int g_iLineIrq;		//line interrupt
extern int g_iSeparate;
extern int g_iLine; 
extern int g_iRealLine;

extern uint8 u8_PredatorCameraBuffer[LINE][COLUMN];     		//Array of images to be original
extern uint8 u8_PendingTreatmentBuffer[LINE][COLUMN];  //Array of images to be processed
extern uint8 u8_FinishProcessingBuffer[LINE][COLUMN]; 	//Array of images to be finish

void PredatorCameraInit(void);
void PORTD_IRQHandler(void);
void DMA_CH1_Handler(void);

#endif
