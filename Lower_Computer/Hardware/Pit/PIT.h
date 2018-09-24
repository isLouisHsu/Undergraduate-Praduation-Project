#ifndef __PIT_H
#define __PIT_H

#include "encoder.h"
#include "control.h"

extern int g_iStopCar;
extern int g_iFlagStopCar;
void Pit0MsInit(uint16 t);
void Pit1MsInit(uint16 t);
void Pit0MsHandler(void);
void Pit1MsHandler(void);



#endif