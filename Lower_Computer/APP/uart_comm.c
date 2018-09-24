//create by meifj 2014-03-23
#include "common.h"
#include "include.h"

volatile uint8 frame[10] = {0};
volatile uint8 frame_ready = 0;
uint8 send_frame[8] = {FIRST_CHAR, SECOND_CHAR};

//接收数据
void uart_comm_handler(uint8 ch)
{
	volatile static int8 cnt = 0;
	volatile static int8 start = 0;
	volatile static int8 len;

	if(frame_ready != 1 && start == 0){
		if(ch == FIRST_CHAR) cnt = 1;		//第一个字符为FIRST_CHAR
		else if(ch == SECOND_CHAR && cnt == 1) cnt = 2;	  //第二个字符为SECOND_CHAR
		else if(cnt == 2){
			start = 1;		// 开接接收数据
			len = ch-1;		// 赋值长度，减去自己的长度
			cnt = 0;		// 计数置0
		}
		else cnt = 0;		// 任何错误的接收，都将cnt置0
		
	}
	else if(start == 1){
		frame[cnt++] = ch;
		// 接收到指定长度字符
		if(cnt == len){
			if(frame[cnt - 1] == LAST_CHAR){
				frame_ready = 1; 
			}
			len = 0;
			start = 0;
			cnt = 0;
		}
	}
	else{
		start = 0;
		frame_ready = 0;
	}
		
}

void uart_send_led(int8 idx, int8 sw)
{	
	send_frame[2] = UART_LED_LEN;
	send_frame[3] = idx + UART_LED1; 
	send_frame[4] = sw;
	send_frame[5] = send_frame[2] + send_frame[3] + send_frame[4];
	send_frame[6] = LAST_CHAR;

	uart_putbuff(UART4, send_frame, UART_LED_LEN+2);
}


void uart_send_param(int8 idx, int8 param1, int8 param2)
{	
	send_frame[2] = UART_PARAM_LEN;
	send_frame[3] = idx + UART_PARAM1; 
	send_frame[4] = param1;
	send_frame[5] = param2;
	send_frame[6] = send_frame[2] + send_frame[3] + send_frame[4] + send_frame[5];
	send_frame[7] = LAST_CHAR;

	uart_putbuff(UART4, send_frame, UART_PARAM_LEN+2);
}


