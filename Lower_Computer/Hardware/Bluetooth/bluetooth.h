#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "common.h"
#include "include.h"
#include "uart_comm.h"
#include "encoder.h"
#include "eaglecamera.h"
#include "motor.h"
#include "control.h"
#include "datatranslate.h"
#include "Imageprocessing.h"

#define BT_UART		UART4
#define BULETOOTH_RX	PTC14
#define BULETOOTH_TX 	PTC15

extern  uint16 BlueTeeth[6];	
extern  uint8  BlueTeeth2[50];


extern  uint8  RxData[10];
extern  uint8  rxsta;
extern  uint8  StartMove;
extern  uint8  Received;
extern  uint8  ReceiveEnable;
extern  uint8  BlueToothSent;

//extern  int16 RxAngle,RxAngleLast;
//extern  int16 RxSpeedLeft,RxSpeedRight;

extern uint8 RxAngle;
extern uint8 RxDirAngle;
extern uint8 RxDirSpeed;
extern uint16 RxSpeed; 
extern int16 RxIntAngle;
extern int16 RxIntAnglelast;
extern int16 RxIntSpeed;
extern uint16 RxDistance;
extern uint8 RxIsInsight;

void BluetoothInit(int BTbaudrate);
void DebugUartInit(int DBGbaudrate);
void uart4_handler(void);
void uart2_handler(void);
void extern_event_process(void);
void Send_buleteeth(void);
void BluetoothParameters(void);
void bluetoothSent(uint8 LeftOrRight, uint8 top, int speed);

#endif 
