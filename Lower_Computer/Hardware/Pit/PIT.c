#include "PIT.h"

int g_iStopCar=0;
int g_iFlagStopCar=0;

void Pit0MsInit(uint16 t)
{
     pit_init_ms(PIT0,t);                  
     set_vector_handler(PIT0_VECTORn,Pit0MsHandler);   // 设置中断复位函数到中断向量表里
     enable_irq(PIT0_IRQn);                         // 使能LPTMR中断
}

void Pit1MsInit(uint16 t)
{
     pit_init_ms(PIT1,t);                  
     set_vector_handler(PIT1_VECTORn,Pit1MsHandler);   // 设置中断复位函数到中断向量表里
     enable_irq(PIT1_IRQn);                         // 使能LPTMR中断
}

void Pit0MsHandler(void)
{
  CVelocityMeasurement();		  //20ms读取编码器
  GoBack();
  MotorPID(g_iSpeedL,g_iSpeedR);
  CMotorDrive(g_iSpeedVauleL,g_iSpeedVauleR);
  PIT_Flag_Clear(PIT0);
}
void Pit1MsHandler(void)
{
        g_iTurnMsCnt++;
        if(g_iFlagBack!=0&&g_iBackMsCnt<1500)g_iBackMsCnt++;
	PIT_Flag_Clear(PIT1);
}

