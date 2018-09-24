#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

#define ON  0
#define OFF 1

#define LED1 PCout(13)
#define LED2 PBout(14)

void LED_GPIO_Config(void);

#endif
