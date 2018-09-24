#include "common.h"
#include "include.h"
#include "motor.h"
#include "control.h"
#include "LedKey.h"
#include "bluetooth.h"
#include "uart_comm.h"
#include "pit.h"
#include "serialport.h"

#define SHOW_DEBUG

void GetData(void);
void DirectionPID(void);
void DirectionControl(void);

uint16 uiMinDistance = 50;

int16 iSpeedSet     = 0;
int16 iSpeedTurnMax = 160;
int16 iSpeedTurnMin = 0;
int16 iSpeedLeft    = 0;
int16 iSpeedRight   = 0;

int main()
{
  BluetoothInit(9600);
  IoLedKeyDialInit();
  MotorInit(500); 
  
  
  CMotorDrive(50,100);while(1);
  
  while(!StartMove)
  {
    //未亮灯时，车停止不动
    if(Received)
    {
      GetData();
      if(RxDistance!=0)StartMove = 1;   //若接收到不为0的距离值，表示车开始启动
    }
  }
  
  
  while(1)
  {
    if(Received)
    {
      GetData();
      DirectionControl();
      CMotorDrive(iSpeedLeft,iSpeedRight);//-1000~1000
      Received = 0;
    }
  }
}

void DirectionControl(void)
{
  if(RxDistance<uiMinDistance)
  {
    //若小车和光源过近，则停止靠近
    iSpeedLeft  = 0;iSpeedRight = 0;
  }
  else
  {
    //若小车和光源较远，则向其行驶
    DirectionPID();
  }
}

void DirectionPID(void)
{
  float P = 0.2;
  float D = 0;
  int16  resultPID = 0;
  
  if(RxIntAngle<-30)
  {
    iSpeedLeft  = iSpeedTurnMin;
    iSpeedRight = iSpeedTurnMax;
  }
  else if(RxIntAngle>30)
  {
    iSpeedLeft  = iSpeedTurnMax;
    iSpeedRight = iSpeedTurnMin;
  }
  else
  {
    resultPID    = (int)( P*RxIntAngle + D*(RxIntAngle-RxIntAnglelast) );
    iSpeedLeft  += resultPID;
    iSpeedRight -= resultPID;
  }
  RxIntAnglelast = RxIntAngle;
  
  //限幅
  if(iSpeedLeft<iSpeedTurnMin)iSpeedLeft = iSpeedTurnMin;
  else if(iSpeedLeft>iSpeedTurnMax)iSpeedLeft = iSpeedTurnMax;
  if(iSpeedRight<iSpeedTurnMin)iSpeedRight = iSpeedTurnMin;
  else if(iSpeedRight>iSpeedTurnMax)iSpeedRight = iSpeedTurnMax;
}

                         
                         
                         
void GetData(void)
{
  //接收数据
  RxDirAngle  = *(RxData+0);
  RxAngle     = *(RxData+1);    
  RxIsInsight = *(RxData+2);    //是否在视野内
  RxDistance  = (*(RxData+5)<<8)|(*(RxData+4));
  
  //角度限幅
  if(RxAngle<3)RxAngle=0;
  else if(RxAngle>160)
  {
    RxDirAngle=0;RxAngle=160;
  }
  
  //计算正负角度
  RxIntAngle = (RxDirAngle==0)?RxAngle:-RxAngle;
  RxIntAngle -= 0;             //角度人为修正
}






















/* ---------------------------- 比赛用程序 --------------------------------
int main()
{	
  BluetoothInit(9600);
  OLED_Init();
  IoLedKeyDialInit();
  EncoderInit();
  SteeringInit();
  MotorInit(10000); 
  
//  CMotorDrive(100,300);while(1);
//   SteeringPwm(g_iSteeringMid);while(1);

	while(!StartMove)	//未亮灯
	{
          OledShow();
		if(Received)
		{
			GetData();
			if(RxDistance!=0)StartMove = 1;
		}
	}
	
  Pit0MsInit(15);
  Pit1MsInit(1);

  while(1)
  {
        OledShow();
  	if(ReceiveEnable)
  	{
         // if(Received)
          if( (Received) && ( (g_iFlagTurn==0)||( (g_iFlagTurn==1)&&(g_iTurnMsCnt>100) ) ) )
          {
            g_iFlagTurn = 0;
            
            GetData();
				     
            SteeringPID();        //舵机PID
			       
            //注：以下两个函数顺序需考虑
            BeaconCounter();
            
            CoreControlC();	  //灯前转弯
               
            SteeringPwm(g_iSteeringValue);
			       
            Received = 0;
          }
  	}
	else
	{
		
	}
    
    // 判断状态
    MovingStateJudge();
  }
}
-------------------------- 比赛用程序结束 ------------------------------*/


















#if 0
int main() 
{
   BluetoothInit(9600);
   //DebugUartInit(9600);
   OLED_Init(); 	
   IoLedKeyDialInit();
  // EagleCameraInit();
   EncoderInit(); 
   SteeringInit();	
   MotorInit(10000);
   Pit0MsInit(15);
   
   while(1)
   {
     SteeringPwm(g_iSteeringMid);
     OledShow(); 
   }
     
for(;;)
   {
   	if(g_iMain == 1)
   	{
          EagalCameraBeaconHandle2();
         // TopJudege();
          SteeringPID();
          //CoreControlCLeft();
          CoreControlCRight();
          SteeringPwm(g_iSteeringValue);
         // SteeringPwm(g_iSteeringLeft);
         // SendMessage();
          g_u8LastTop= g_u8Top;
        }
        g_iMain=0;
  	g_u8FFPoint = 0 ;
  	g_u8FSPoint = 0 ;
        gpio_turn(PTC1);

    OledShow(); 
   }

} 
#endif