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
	//��������
  rxAngleDir  = *(rxData+0);		//���ʱΪ"0"���ұ�ʱΪ"1"
  rxAngle     = *(rxData+1);    
  rxIsInsight = *(rxData+2);    //�Ƿ�����Ұ��
  rxDistance  = (*(rxData+5)<<8)|(*(rxData+4));
  
  //�Ƕ��޷�
  if(rxAngle<3)rxAngle=0;
  else if(rxAngle>160)
  {
    rxAngleDir=0;rxAngle=160;
  }
  
  //����int�ͽǶȣ����ʱΪ"+"���ұ�ʱΪ"-"
  rxIntAngle = (rxAngleDir==0)?rxAngle:-rxAngle;
}


void directionControl(void)
{
	if(rxDistance<40)
  {
    //�������ű�ƹ�����ֹͣ
    iSpeedLeft  = 0;iSpeedRight = 0;
  }
  else
  {
    //�������ű�ƽ�Զ�����
    //directionPID();
		directionBinary();
  }
}

void directionBinary(void)
{
#if 0
	if(rxIntAngle<-15)			//���Ҳ�30������
	{
    iSpeedLeft  = iSpeedTurnInside;
    iSpeedRight = iSpeedTurnOutside;
	}
	else if(rxIntAngle>15)	//�����30������
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
	if(rxIntAngle<-25)			//���Ҳ�30������
	{
    iSpeedLeft  = iSpeedSetLeft/3;
    iSpeedRight = iSpeedSetRight;
	}
	else if(rxIntAngle>25)	//�����30������
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
	
	if(rxIntAngle<-36)			//���Ҳ�30������
	{
    iSpeedLeft  = iSpeedTurnInside;
    iSpeedRight = iSpeedTurnOutside;
	}
	else if(rxIntAngle>36)	//�����30������
	{
    iSpeedLeft  = iSpeedTurnOutside;
    iSpeedRight = iSpeedTurnInside;
	}
	else
	{
		//�����ʱ�������"+"ֵ����ʱӦ�У�iSpeedLeft > iSpeedRight
		//���Ҳ�ʱ�������"-"ֵ����ʱӦ�У�iSpeedLeft < iSpeedRight
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
