#ifndef __DATATRANSLATE_H
#define __DATATRANSLATE_H

#include "encoder.h"
#include "eaglecamera.h"
#include "control.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))			
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))	
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

extern uint8 Data_Check,Send_Status,Send_Senser,Send_Offset,Send_PID1,Send_PID2,Send_PID3,Send_PID4,Send_PID5,Send_PID6;
extern uint8 data_to_send[50];
/*
extern unsigned char RxBuffer[50];
extern unsigned char RxState;*/

extern int g_iFlagStart;


void Data_Receive_Anl(uint8 *data_buf,uint8 num);  			
void Data_Send_PID1(void);								
void Data_Send_PID2(void);							
void Data_Send_PID3(void);							
void Data_Send_Senser(void);						
void Data_Send_MotoPWM(void);							
void Data_Send_Check(uint16 check);	
void Data_Receive(unsigned char com_data);
void Data_Send_Line(void);					
//void Data_Send_Status(void);	
						
#endif
