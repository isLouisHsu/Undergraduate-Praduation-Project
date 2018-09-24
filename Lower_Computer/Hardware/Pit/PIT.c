#include "PIT.h"

int g_iStopCar=0;
int g_iFlagStopCar=0;

void Pit0MsInit(uint16 t)
{
     pit_init_ms(PIT0,t);                  
     set_vector_handler(PIT0_VECTORn,Pit0MsHandler);   // �����жϸ�λ�������ж���������
     enable_irq(PIT0_IRQn);                         // ʹ��LPTMR�ж�
}

void Pit1MsInit(uint16 t)
{
     pit_init_ms(PIT1,t);                  
     set_vector_handler(PIT1_VECTORn,Pit1MsHandler);   // �����жϸ�λ�������ж���������
     enable_irq(PIT1_IRQn);                         // ʹ��LPTMR�ж�
}

void Pit0MsHandler(void)
{
  CVelocityMeasurement();		  //20ms��ȡ������
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

