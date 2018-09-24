#ifndef __SERIALPORT_H
#define __SERIALPORT_H

#include "common.h"
#include "include.h"

#define DEBUG_UART		UART2
#define UART_RX			PTD2
#define UART_TX			PTD3


void DebugUartInit(int DBbaudrate);	
void uart2_handler(void);

#endif 