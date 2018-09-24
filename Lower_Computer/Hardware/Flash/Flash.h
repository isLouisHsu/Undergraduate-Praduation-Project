#ifndef __FLASH_H
#define __FLASH_H

#include "MK60_flash.h"
#include "oled.h"
#include "control.h"
#include "steering.h"

void FlashInit(int FlashNumber);
void FlashWrite(void);
void FlashRead(void);


#endif