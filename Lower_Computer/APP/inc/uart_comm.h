//create by meifj 2014-03-23
#ifndef __COMM_H
#define __COMM_H

#include "common.h"
#include "include.h"
#include "bluetooth.h"

#define FIRST_CHAR	0xA5	// 协议头1
#define SECOND_CHAR	0x5A	// 协议头2
#define LAST_CHAR	0xAA	// 协议头3

/* 在串口接收中断中调用uart_comm_handler
	若完整接收到一桢数据那么frame_finish 置1
*/


#define UART_SLIDE1  	0xF1
#define UART_SLIDE2  	0xF2
#define UART_SLIDE3  	0xF3

#define UART_KEY1 		0XB1
#define UART_KEY2 		0XB2
#define UART_KEY3 		0XB3
#define UART_KEY4 		0XB4
#define UART_KEY5 		0XB5
#define UART_KEY6 		0XB6
#define UART_KEY7 		0XB7
#define UART_KEY8 		0XB8
#define UART_KEY9 		0XB9
#define UART_KEY10 		0XBA
#define UART_KEY11 		0XBB
#define UART_KEY12 		0XBC

#define UART_LED_LEN    0x05
#define UART_LED1  		0xE1
#define UART_LED2  		0xE2
#define UART_LED3  		0xE3
#define UART_LED4  		0xE4
#define UART_LED5  		0xE5
#define UART_LED6  		0xE6
#define UART_LED7  		0xE7
#define UART_LED8  		0xE8

#define UART_PARAM_LEN	0x06
#define UART_PARAM1 	0xC1
#define UART_PARAM2 	0xC2
#define UART_PARAM3 	0xC3
#define UART_PARAM4 	0xC4
#define UART_PARAM5 	0xC5
#define UART_PARAM6 	0xC6



extern volatile uint8 frame[10];
extern volatile uint8 frame_ready;

void uart_comm_handler(uint8 ch);

//idx 索引  sw 1:亮, 0灭
void uart_send_led(int8 idx, int8 sw);
void uart_send_param(int8 idx, int8 param1, int8 param2);

#endif

