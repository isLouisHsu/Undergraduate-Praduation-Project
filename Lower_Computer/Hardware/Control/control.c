#include "control.h"

/****************Steering gear parameters********************/
uint32 g_iSteeringValue = 140; 
uint32 g_iSteeringOutput = 0;
uint32 g_iSteeringMid = 140;    
uint32 g_iSteeringLeft =157;//+17
uint32 g_iSteeringRight =126;//-14
uint32 g_iSteeringLeftRange=0;
uint32 g_iSteeringRightRange=0;
uint32 g_iSteeringAdd=0;

float g_fSteeringP = 0.28;  //0621:0.35     //to do:���PID�ֶ�
float g_fSteeringI = 0;
float g_fSteeringD = 0.01;

float g_fSteeringCoefficientP1 = 1.0;
float g_fSteeringCoefficientP2 = 1.0; 
float g_fSteeringCoefficientP3 = 1.0;
float g_fSteeringCoefficientP4 = 1.0;

float g_fSteeringCoefficientD1 = 1.0;
float g_fSteeringCoefficientD2 = 1.0;
float g_fSteeringCoefficientD3 = 1.0;
float g_fSteeringCoefficientD4 = 1.0;

/************************************************************/

/****************Steering gear parameters********************/
float g_fSpeedP =7;     //7  
float g_fSpeedI =3;     //3 
float g_fSpeedD =0.05;  //0.05

uint32 g_u32SpeedP ;
uint32 g_u32SpeedI ;
uint32 g_u32SpeedD ;
/*
float g_fSpeedP =4.00; //20  
float g_fSpeedI =1.00;    //2
float g_fSpeedD = 0.10;*/
/*
float g_fSpeedP1 =5.00; //20  
float g_fSpeedI1 =1.50;    //2
float g_fSpeedD1 = 0.01;
*/
int  g_iFlagSlowCount =0 ;
int  g_iFlagSlow=0;
int  g_iTurnMsCnt = 0;
int  g_iBackMsCnt = 0;

int g_iSpeed;
int g_iSpeedL=0;
int g_iSpeedR=0;
int g_iSpeedInsideBack = -80;
int g_iSpeedOutsideBack = -80;
int g_iSpeedInside = 120;//80;     // ת����٣����ڲ���
int g_iSpeedOutside = 180;//120;   // ת����٣��������
int g_iSpeedVaule = 0;
int g_iSpeedVauleL= 0;
int g_iSpeedVauleR= 0;
int g_iSpeedDifferentialL =220;   //100
int g_iSpeedDifferentialR = 120;  //180
int g_iFlagLR=1;
int g_iFlagTop = 0;
int g_iFlagSend = 0;
int g_iFlagTurn = 0;
int g_iFlagBack = 0;

uint8 g_u8SteeringErrorL[20] = 	{	11,	12,	12,	12,	12,	12,	13,	13,	13,	13,	13,	13,	13,	13,	13};
uint8 g_u8SteeringErrorR[20] = 	{	15,	16,	18,	20,	16,	16,	13,	13,	13,	13,	13,	13,	13,	13,	13};
//uint8 g_u8SlowDown[20]	     =	{	35,	35,	35,	35,	35,	35,	30,	30,	30,	30,	30,	30,	30,	30,	30};

int  g_iSpeedSet =225;
int  g_iSpeedSetSlowDown = 180;//�����ٶ�

/************************************************************/
//g_u8TurnDir:'0' go left;'1' go right
//����index���ű�Ƹ���
uint8 g_u8TurnDir[20] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
//uint8 g_u8TurnDir[20] = { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1};
//uint8 g_u8TurnDir[20] = { 1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1};
//uint8 g_u8TurnDir[20] =   { 0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1};

//�����ٶȲ�ͬ���Ӳ�ͬ���뿪ʼ���٣��Ӳ�ͬ��ƫ��
//����indexΪ�ٶȵ�λ                                                           L R              
//�ٶ�����		                90	120	150	180	210	240	270	300	330	360	390	420	450	
//�����ٶ�                              75      105     135     165     195     225     255     285     315     345     375     405     435       
uint8 g_u8TopL[20]           =  {       28,     33,     38,     43,     47,     53,     55,     62,     67,     88,     98,     108};
uint8 g_u8TopR[20]           =  {       28,     33,     38,     43,     52,     57,     63,     62,     75,     88,     98,     108};
uint16 g_iDistanceNear = 45;
uint16 g_iDistanceFar  = 90;
int g_iNear  = 0;
int g_iFar   = 0;
int g_iCount = 0;
int g_iAccelerate = 0;

int g_iLightCheck = 0;
int g_iLightCheckN = 0;
int g_iLightCheckF = 0;

int g_iSpeedSetAverage = 0;
uint16 g_iAverageSpeedMin = 100;
float g_fAverageSpeedMin = 0.20;

uint8 g_u8MovingSta = 0;
//'0':ֹͣ
//'1':ǰ��
//'2':����


// ���Ŀ���
void CoreControlC(void)
{
  static uint8 outSightCnt=0;
  
  // ������������������������������������Ϊ��ת������������������������������������
  if(g_u8TurnDir[g_iCount] == 0)
  {
    if(RxIsInsight==1)
    {
      outSightCnt = 0;
      g_iSteeringAdd = 0;
      
#if 0 //��ǰ���� 2017/6/30
      if(RxDistance>50)
      {
        g_iSpeedL = g_iSpeedSet;
        g_iSpeedR = g_iSpeedSet;
      }
      else
      {
        g_iSpeedL = g_iSpeedSetSlowDown;
        g_iSpeedR = g_iSpeedSetSlowDown;
      }
#elif 1
      SpeedRelateToSteer();
#elif 0
      g_iSpeedL = g_iSpeedSet;
      g_iSpeedR = g_iSpeedSet;
#endif
      
      if(g_iAverageSpeed<=90)
      {
       if(RxDistance <= g_u8TopL[0])
       { 
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[0], g_iAverageSpeed); 
//#endif
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[0], g_iAverageSpeed); 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=120)
      {
       if(RxDistance <= g_u8TopL[1])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[1], g_iAverageSpeed);
//#endif   
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[1], g_iAverageSpeed);
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=150)
      {
       if(RxDistance <= g_u8TopL[2])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[2], g_iAverageSpeed);
//#endif 
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[2], g_iAverageSpeed);
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=180)
      {
       if(RxDistance <= g_u8TopL[3])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[3], g_iAverageSpeed); 
//#endif  
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[3], g_iAverageSpeed); 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=210)
      {
       if(RxDistance <= g_u8TopL[4])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[4], g_iAverageSpeed);  
//#endif  
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[4], g_iAverageSpeed);
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=240)
      {
       if(RxDistance <= g_u8TopL[5])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[5], g_iAverageSpeed); 
//#endif   
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[5], g_iAverageSpeed);
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=270)
      {
       if(RxDistance <= g_u8TopL[6])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[6], g_iAverageSpeed); 
//#endif  
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[6], g_iAverageSpeed); 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=300)
      {
       if(RxDistance <= g_u8TopL[7])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[7], g_iAverageSpeed); 
//#endif 
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[7], g_iAverageSpeed);
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=330)
      {
       if(RxDistance <= g_u8TopL[8])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[8], g_iAverageSpeed);  
//#endif
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[8], g_iAverageSpeed);  
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=360)
      {
       if(RxDistance <= g_u8TopL[9])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[9], g_iAverageSpeed);
//#endif  
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[9], g_iAverageSpeed);
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=390)
      {
       if(RxDistance <= g_u8TopL[10])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[10], g_iAverageSpeed); 
//#endif  
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[10], g_iAverageSpeed); 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=420)
      {
       if(RxDistance <= g_u8TopL[11])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[11], g_iAverageSpeed); 
//#endif 
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[11], g_iAverageSpeed);
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else if(g_iAverageSpeed<=450)
      {
       if(RxDistance <= g_u8TopL[12])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[12], g_iAverageSpeed); 
//#endif 
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[12], g_iAverageSpeed); 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
      else
      {
       if(RxDistance <= g_u8TopL[13])
       {
//#ifdef SHOW_DEBUG
//         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[13], g_iAverageSpeed); 
//#endif
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopL[13], g_iAverageSpeed); 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringLeft;
         g_iSpeedL = g_iSpeedInside;
         g_iSpeedR = g_iSpeedOutside;
       }
      }
    }
    else if(RxIsInsight==2)
    {
      outSightCnt = 0;
      g_iSteeringAdd = 0;
      SpeedRelateToSteer();
    }
    else  //����Ұ
    {
      if(g_iSteeringAdd<5)
      {
        outSightCnt++;
        if(outSightCnt>=15)
        {
          g_iSteeringAdd += 1;
          outSightCnt = 0;
        }
      }
      if(g_iSteeringValue<g_iSteeringMid)
        g_iSteeringValue += g_iSteeringAdd;
      else
        g_iSteeringValue -= g_iSteeringAdd;
      
      //g_iSteeringValue = g_iSteeringLeft;
      //g_iSpeedL = g_iSpeedInside;
      //g_iSpeedR = g_iSpeedOutside;
    }
  }
  
  
  
  // ������������������������������������Ϊ��ת������������������������������������
  else  // ����ת��
  {
    if(RxIsInsight==1)
    { 
      outSightCnt = 0;
      g_iSteeringAdd = 0;
      
#if 0 //��ǰ���� 2017/6/30
      if(RxDistance>50)
      {
        g_iSpeedL = g_iSpeedSet;
        g_iSpeedR = g_iSpeedSet;
      }
      else
      {
        g_iSpeedL = g_iSpeedSetSlowDown;
        g_iSpeedR = g_iSpeedSetSlowDown;
      }
#elif 1
      SpeedRelateToSteer();
#elif 0
      g_iSpeedL = g_iSpeedSet;
      g_iSpeedR = g_iSpeedSet;
#endif
      
      if(g_iAverageSpeed<=90)
      {
       if(RxDistance <= g_u8TopR[0])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[0], g_iAverageSpeed); 
#endif 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=120)
      {
       if(RxDistance <= g_u8TopR[1])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[1], g_iAverageSpeed); 
#endif 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=150)
      {
       if(RxDistance <= g_u8TopR[2])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[2], g_iAverageSpeed); 
#endif  
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=180)
      {
       if(RxDistance <= g_u8TopR[3])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[3], g_iAverageSpeed); 
#endif   
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=210)
      {
       if(RxDistance <= g_u8TopR[4])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[4], g_iAverageSpeed); 
#endif  
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=240)
      {
       if(RxDistance <= g_u8TopR[5])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[5], g_iAverageSpeed); 
#endif  
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=270)
      {
       if(RxDistance <= g_u8TopR[6])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[6], g_iAverageSpeed); 
#endif   
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=300)
      {
       if(RxDistance <= g_u8TopR[7])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[7], g_iAverageSpeed); 
#endif 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=330)
      {
       if(RxDistance <= g_u8TopR[8])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[8], g_iAverageSpeed); 
#endif 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=360)
      {
       if(RxDistance <= g_u8TopR[9])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[9], g_iAverageSpeed); 
#endif  
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=390)
      {
       if(RxDistance <= g_u8TopR[10])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[10], g_iAverageSpeed); 
#endif  
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=420)
      {
       if(RxDistance <= g_u8TopR[11])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[11], g_iAverageSpeed); 
#endif   
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else if(g_iAverageSpeed<=450)
      {
       if(RxDistance <= g_u8TopR[12])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[12], g_iAverageSpeed); 
#endif  
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
      else
      {
       if(RxDistance <= g_u8TopL[13])
       {
#ifdef SHOW_DEBUG
         bluetoothSent(g_u8TurnDir[g_iCount], g_u8TopR[13], g_iAverageSpeed); 
#endif 
         g_iFlagTurn = 1;g_iTurnMsCnt = 0;
         g_iSteeringValue = g_iSteeringRight;
         g_iSpeedL = g_iSpeedOutside;
         g_iSpeedR = g_iSpeedInside;
       }
      }
    }
    else if(RxIsInsight==2)
    {
      outSightCnt = 0;
      g_iSteeringAdd = 0;
      SpeedRelateToSteer();
    }
    else  //����Ұ
    {
      if(g_iSteeringAdd<5)
      {
        outSightCnt++;
        if(outSightCnt>=15)
        {
          g_iSteeringAdd += 1;
          outSightCnt = 0;
        }
      }
      if(g_iSteeringValue<g_iSteeringMid)
        g_iSteeringValue += g_iSteeringAdd;
      else
        g_iSteeringValue -= g_iSteeringAdd;
      
      //g_iSteeringValue = g_iSteeringRight;
      //g_iSpeedL = g_iSpeedOutside;
      //g_iSpeedR = g_iSpeedInside;
    }
  }
   g_iSpeedSetAverage = (g_iSpeedL + g_iSpeedR)/2;
}

//2017/6/30
void SpeedRelateToSteer(void)
{
    if(g_iSteeringValue <=130)			// < ����
    {
	g_iSpeedL = g_iSpeedOutside;
        g_iSpeedR = g_iSpeedInside;
    }
    else if(g_iSteeringValue >=156)	// >����
    {
      g_iSpeedL =g_iSpeedInside ;
      g_iSpeedR = g_iSpeedOutside;
    }
    else      //���ֵ��
    {
      //g_iSpeedL = g_iSpeedSet;
      //g_iSpeedR = g_iSpeedSet;
     
      if(RxDistance > 100)
      {
        g_iSpeedL = g_iSpeedSet;
        g_iSpeedR = g_iSpeedSet;
      }
      else
      {
        g_iSpeedL = g_iSpeedSetSlowDown;
        g_iSpeedR = g_iSpeedSetSlowDown;
      }
      
    }
#if 0
	uint32 steerError = ABS(g_iSteeringValue- g_iSteeringMid);
	float  steerCoff = 0;


	if(RxDistance > 60)
	{
		if(g_iSteeringValue < g_iSteeringMid)			// < ����
		{
			steerCoff = (float)(steerError)/(float)(g_iSteeringRightRange);
			g_iSpeedL = g_iSpeedOutside+(g_iSpeedSet-g_iSpeedOutside)*steerCoff;
			g_iSpeedR = g_iSpeedInside +(g_iSpeedSet-g_iSpeedInside )*steerCoff;
		}
		else if(g_iSteeringValue > g_iSteeringMid)	// >����
		{
			steerCoff = (float)(steerError)/(float)(g_iSteeringLeftRange);
			g_iSpeedL = g_iSpeedInside +(g_iSpeedSet-g_iSpeedInside )*steerCoff;
			g_iSpeedR = g_iSpeedOutside+(g_iSpeedSet-g_iSpeedOutside)*steerCoff;
		}
		else											// ==
		{
			g_iSpeedL = g_iSpeedSet;
			g_iSpeedR = g_iSpeedSet;
		}
	}
	else
	{
		//g_iSpeedL = g_iSpeedSetSlowDown;
	//	g_iSpeedR = g_iSpeedSetSlowDown;
                g_iSpeedL = g_iSpeedSet;
			g_iSpeedR = g_iSpeedSet;
	}
#endif
}

// ����
void MovingStateJudge(void)
{
    g_iSpeedSetAverage = (g_iSpeedL + g_iSpeedR)/2;
  
	if((g_iSpeedL==0)&&(g_iSpeedR==0))
	{
		g_u8MovingSta = 0;
	}
	else if((g_iSpeedL>0)&&(g_iSpeedR>0))
	{
		g_u8MovingSta = 1;
	}
	else if((g_iSpeedL<0)&&(g_iSpeedR<0))
	{
		g_u8MovingSta = 2;
	}
}

void GoBack()
{
	static u8 cnt=0;
	static u8 cntBack = 0;
        uint16 averageSpeedMin = 0;
        
          
        //�����ٶ���ֵ���� 2017/6/30
        /*if(g_iAverageSpeed>0)
        {
          if(g_iAverageSpeed<150)     averageSpeedMin = 150*0.3;  //45
          else if(g_iAverageSpeed<240)averageSpeedMin = 240*0.2;  //48
          else if(g_iAverageSpeed<330)averageSpeedMin = 330*0.15; //49.5
          else if(g_iAverageSpeed<420)averageSpeedMin = 420*0.12; //50.4
        }*/
        
	if((g_u8MovingSta==1)&& ((g_iFlagBack==0)|| ((g_iFlagBack==1)&&(g_iBackMsCnt>800))) )	//�趨ֵΪ������Ӧ����ǰ
	{
		//if(g_iAverageSpeed < g_fAverageSpeedMin*g_iSpeedSetAverage)	//���Ǳ�����ֵ��С����ʾ��ס
		//if(g_iAverageSpeed < averageSpeedMin)
                if(g_iAverageSpeed < 50)
                {
			cnt++;
			if(cnt==12)
			{
                                g_iFlagBack = 1;
				if(g_u8TurnDir[g_iCount]==0)
				{
					g_iSteeringValue = g_iSteeringLeft;
					g_iSpeedL = g_iSpeedOutsideBack;
					g_iSpeedR = g_iSpeedOutsideBack;
				}
				else
				{
					g_iSteeringValue = g_iSteeringRight;
					g_iSpeedL = g_iSpeedOutsideBack;
					g_iSpeedR = g_iSpeedOutsideBack;
				}
				ReceiveEnable = 0;
				g_u8MovingSta = 2;
				cnt = 0;
			}
		}
		else
		{
			cnt = 0;
		}
	}
	else if(g_u8MovingSta==2)	//�趨ֵΪ������Ӧ������
	{
		cntBack++;
		if(cntBack>=50)
		{
                        g_iBackMsCnt=0;
			ReceiveEnable = 1;
			cntBack = 0;
		} 
	}
}

// �ű������
void BeaconCounter(void)
{
  if(RxIsInsight!=1)return;
  if(RxDistance < g_iDistanceNear)
  {
    g_iNear = 1;
  }
  if((1==g_iNear)&&(RxDistance > g_iDistanceFar))
  {
    g_iNear = 0;
    g_iCount++;
    BlueToothSent = 0;
//#ifdef SHOW_DEBUG
//    printf("C\n");
//#endif
    printf("C\n");
  }
}

// ���Ŀ���
void CoreControl(void)
{
    if(RxIsInsight) //��Ұ��
    {      
    	g_iSpeedL = g_iSpeedSet;
      	g_iSpeedR = g_iSpeedSet;
    }
    else  //��Ұ��
    {
    	g_iSteeringValue = g_iSteeringLeft;
	g_iSpeedL = g_iSpeedInside;
	g_iSpeedR = g_iSpeedOutside;
    }
   g_iSpeedSetAverage = (g_iSpeedL + g_iSpeedR)/2;
}


void AddSteerError()
{
  if(RxDistance>35)
  {
	if(ABS(RxIntAngle)<30)	//����ͷ��׼�Ʒ�����
	{
		if(g_u8TurnDir[g_iCount] == 0)	//Ҫ�ӵ���߹�ȥ
		{
			RxIntAngle -= 15;
		}
		else							//Ҫ�ӵ��ұ߹�ȥ
		{
			RxIntAngle += 15;
		}
	}
  }
  else
  {
    RxIntAngle = 0;
  }
}

void AddSteerOutError(void)
{
  if(RxDistance<30)
  {
    if(g_u8TurnDir[g_iCount] == 0)	//Ҫ�ӵ���߹�ȥ
    {
      g_iSteeringValue += 10;
    }
    else                                //Ҫ�ӵ��ұ߹�ȥ
    {
      g_iSteeringValue -= 10;
    }
  }
}

void SteeringPID(void)
{
#if 1 //���PID�ֶ� 2017/6/30
  g_fDeviation = RxIntAngle;
  g_fTwoDeviation = g_fDeviation - g_fLastDeviation;
  
  if(g_iAverageSpeed<=180)      g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP1*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD1*g_fSteeringD*g_fTwoDeviation));	//PID
  else if(g_iAverageSpeed<=360) g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP2*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD2*g_fSteeringD*g_fTwoDeviation));	//PID
  else if(g_iAverageSpeed<=480) g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP3*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD3*g_fSteeringD*g_fTwoDeviation));	//PID
  else 			        g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP4*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD4*g_fSteeringD*g_fTwoDeviation));	//PID
  
  g_fLastDeviation = g_fDeviation;
#endif
  
  //����ʽ
#if 0
    if(RxIntAngle<-30)
      g_iSteeringValue = g_iSteeringLeft;
    else if(RxIntAngle>30)
      g_iSteeringValue = g_iSteeringRight;
    else
    //g_iSteeringValue =(int) (g_iSteeringMid+( g_fSteeringP*RxAngle + g_fSteeringD*(RxAngle-RxAngleLast)));
    	g_iSteeringValue =(int) (g_iSteeringMid - ( g_fSteeringP*RxIntAngle));
#endif
  
  //left and right limit
  if(g_iSteeringValue>=g_iSteeringLeft)	
    g_iSteeringValue = g_iSteeringLeft;
  else if(g_iSteeringValue<=g_iSteeringRight)
    g_iSteeringValue = g_iSteeringRight;
}

//if 0
//void SteeringPID(void)
//{
//	//PID
//#if 0
//	g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringP*g_fDeviation + g_fSteeringD*g_fTwoDeviation));	//PID
//#endif
//#if 0
//	if(g_iAverageSpeed<=300)		g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP1*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD1*g_fSteeringD*g_fTwoDeviation));	//PID
//	else if(g_iAverageSpeed<=500)	        g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP2*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD2*g_fSteeringD*g_fTwoDeviation));	//PID
//	/*else if(g_iAverageSpeed<=400)	        g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP3*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD3*g_fSteeringD*g_fTwoDeviation));	//PID
//	else 							g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP4*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD4*g_fSteeringD*g_fTwoDeviation));	//PID
//*/
//#endif
//#if 0
//        if(  g_iSpeedError<=30 &&  g_iSpeedError>=-30)		g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP1*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD1*g_fSteeringD*g_fTwoDeviation));	//PID
//	 	
//	else if(g_iSpeedError>=30 ||g_iSpeedError<=-30) 	g_iSteeringValue =(int) (g_iSteeringMid-( g_fSteeringCoefficientP3*g_fSteeringP*g_fDeviation + g_fSteeringCoefficientD3*g_fSteeringD*g_fTwoDeviation));	//PID
//	
//        
//#endif
//      
//	/*
//	**left and right limit
//	*/
//	if(g_iSteeringValue>=g_iSteeringLeft)	
//	 g_iSteeringValue = g_iSteeringLeft;
//	else 
//	 if(g_iSteeringValue<=g_iSteeringRight)
//	  g_iSteeringValue = g_iSteeringRight;
//}
//#endif

void MotorPID(int speed_parameter1,int speed_parameter2)
{
	static int errorL=0,errorR=0,doubleerrorL=0,doubleerrorR=0,lasterrorL=0,lasterrorR=0,doublelasterrorL=0,doublelasterrorR=0;
	float incL=0,incR=0;

	errorL = speed_parameter1 - g_i16LeftVal;
	doubleerrorL = errorL - lasterrorL;
        
        errorR = speed_parameter2 - g_i16RightVal;
	doubleerrorR = errorR - lasterrorR;

	incL =(float)(g_fSpeedP*doubleerrorL+g_fSpeedI*errorL+g_fSpeedD*(errorL-2*lasterrorL+doublelasterrorL));
	g_iSpeedVauleL=(int)(incL+g_iSpeedVauleL) ;   
    if(g_iSpeedVauleL>=999)
		g_iSpeedVauleL =999;
	if(g_iSpeedVauleL <= -999)
		g_iSpeedVauleL =-999;
        
    incR =(float)(g_fSpeedP*doubleerrorR+g_fSpeedI*errorR+g_fSpeedD*(errorR-2*lasterrorR+doublelasterrorR));
	g_iSpeedVauleR=(int)(incR+ g_iSpeedVauleR) ; 
    if(g_iSpeedVauleR>=999)
		g_iSpeedVauleR =999;
	if(g_iSpeedVauleR <= -999)
		g_iSpeedVauleR =-999;

        doublelasterrorL = lasterrorL;		
	lasterrorL = errorL;
	
        doublelasterrorR = lasterrorR;	
	lasterrorR = errorR;
	
}


