#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"

void getData(void);
void directionControl(void);
void directionPID(void);
void directionBinary(void);

u8 isStartMove = 0;
float p = 5;
float d = 0;

int main(void)
{
	delay_init();
	uart1_init(9600);	 			//PA9-TX;PA10-RX;9600
	LED_GPIO_Config();			//PC13-LED1
	TIM2PwmInit();					//PA0~PA3 - TIM2_CH1~4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//TIM2PwmOutput(600,300);
	TIM2PwmOutput(0,0);
	
	while(!isStartMove)
  {
    if(isReceived)
    {
      getData();
      if(rxDistance!=0)isStartMove = 1;
			isReceived = 0;
    }
  }
	while(1)
	{
		if(isReceived)
    {
      getData();
      directionControl();
			TIM2PwmOutput(iSpeedLeft,iSpeedRight);
			isReceived = 0;
    }
	}
}

void getData(void)
{
	//解析数据
  rxAngleDir  = *(rxData+0);		//左边时为"0"，右边时为"1"
  rxAngle     = *(rxData+1);    
  rxIsInsight = *(rxData+2);    //是否在视野内
  rxDistance  = (*(rxData+5)<<8)|(*(rxData+4));
  
  //角度限幅
  if(rxAngle<3)rxAngle=0;
  else if(rxAngle>160)
  {
    rxAngleDir=0;rxAngle=160;
  }
  
  //计算int型角度，左边时为"+"，右边时为"-"
  rxIntAngle = (rxAngleDir==0)?rxAngle:-rxAngle;
}


void directionControl(void)
{
	if(rxDistance<40)
  {
    //若距离信标灯过近则停止
    iSpeedLeft  = 0;iSpeedRight = 0;
  }
  else
  {
    //若距离信标灯较远则跟随
    //directionPID();
		directionBinary();
  }
}

void directionBinary(void)
{
#if 0
	if(rxIntAngle<-15)			//在右侧30度以外
	{
    iSpeedLeft  = iSpeedTurnInside;
    iSpeedRight = iSpeedTurnOutside;
	}
	else if(rxIntAngle>15)	//在左侧30度以外
	{
    iSpeedLeft  = iSpeedTurnOutside;
    iSpeedRight = iSpeedTurnInside;
	}
	else
	{
		iSpeedLeft  = iSpeedSetLeft;
		iSpeedRight = iSpeedSetRight;
	}
#else
	if(rxIntAngle<-25)			//在右侧30度以外
	{
    iSpeedLeft  = iSpeedSetLeft/3;
    iSpeedRight = iSpeedSetRight;
	}
	else if(rxIntAngle>25)	//在左侧30度以外
	{
    iSpeedLeft  = iSpeedSetLeft;
    iSpeedRight = iSpeedSetRight/3;
	}
	else
	{
		iSpeedLeft  = iSpeedSetLeft;
		iSpeedRight = iSpeedSetRight;
	}
#endif
}

void directionPID(void)
{
	int16_t resultPID = 0;
	
	if(rxIntAngle<-36)			//在右侧30度以外
	{
    iSpeedLeft  = iSpeedTurnInside;
    iSpeedRight = iSpeedTurnOutside;
	}
	else if(rxIntAngle>36)	//在左侧30度以外
	{
    iSpeedLeft  = iSpeedTurnOutside;
    iSpeedRight = iSpeedTurnInside;
	}
	else
	{
		//在左侧时，计算得"+"值，此时应有：iSpeedLeft > iSpeedRight
		//在右侧时，计算得"-"值，此时应有：iSpeedLeft < iSpeedRight
		resultPID   = (int)( p*rxIntAngle + d*(rxIntAngle-rxIntAngleLast) );
    iSpeedLeft  = iSpeedSetLeft  + resultPID;
    iSpeedRight = iSpeedSetRight - resultPID;
	}
	rxIntAngleLast = rxIntAngle;
	
	if(iSpeedLeft<iSpeedTurnInside)iSpeedLeft = iSpeedTurnInside;
  else if(iSpeedLeft>iSpeedTurnOutside)iSpeedLeft = iSpeedTurnOutside;
  if(iSpeedRight<iSpeedTurnInside)iSpeedRight = iSpeedTurnInside;
  else if(iSpeedRight>iSpeedTurnOutside)iSpeedRight = iSpeedTurnOutside;
}
