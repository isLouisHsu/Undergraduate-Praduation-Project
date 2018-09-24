#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"




/*
 * Include 用户自定义的头文件
 */
#include  "MK60_wdog.h"
#include  "MK60_adc.h"
#include  "MK60_gpio.h"     //IO口操作
#include  "MK60_uart.h"     //串口
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //低功耗定时器(延时)
#include  "MK60_pit.h"      //PIT
#include  "MK60_FLASH.h"    //FLASH
#include  "MK60_FTM.h"
#include  "MK60_spi.h"
#include  "MK60_dma.h"

#include  "FIRE_LED.H"          //LED
#include  "FIRE_KEY.H"          //KEY

//#include  "pin_define.h"
//#include  "uart_comm.h"
//#define K60_TEST
#endif  //__INCLUDE_H__
