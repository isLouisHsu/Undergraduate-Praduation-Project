#include "encoder.h"

int16 g_i16LeftVal=0,g_i16RightVal=0,g_i16LastLeftVal=0,g_i16LastRightVal=0;
int g_iAverageSpeed=0,g_iLastAverageSpeed=0;
int g_iFlagCount1 = 0;
int g_iFlagStable = 0;
int g_iProtectMotor = 0;
int g_iProtectFlag = 0 ;
int g_iStopMotor = 0 ;
int g_iStableGrade15 = 0;
int g_iStableGrade45 = 0;
int g_iStableGrade75 = 0;
int g_iStableGrade105 = 0;

int g_iStableGrade275 = 0;
int g_iVCount275 = 0;

int g_iStableGrade325 = 0;
int g_iVCount325 = 0;
int g_iStableGrade375 = 0;
int g_iVCount375 = 0;
int g_iStableGrade425 = 0;
int g_iVCount425 = 0;
int g_iStableGrade475 = 0;
int g_iVCount475 = 0;


int g_iVCount1 = 0;
int g_iVCount2 = 0;
int g_iVCount3 = 0;
int g_iVCount4 = 0;

int g_iSpeedError = 0;

/*
** EncoderInit
*/
void EncoderInit(void)
{
	/*
	**FTM1 orthogonal decoding initialization
	*/
	FTM_QUAD_Init(COUNTER1_FTM);                     
        port_init_NoALT(COUNTER1_A, PULLUP);       
        port_init_NoALT(COUNTER1_B, PULLUP);

	/*
	**DMA velocity measurement:Can not judge positive and negative
	*/
#if 1
        set_vector_handler(DMA2_VECTORn , DMA_CH2_Handler);
	DMA_count_Init(DMA_CH2, PTE1, 0x7FFF, DMA_rising_up);   //DMA, PTE5
	DMA_EN(DMA_CH2);
	DMA_IRQ_EN(DMA_CH2);
#endif
}

/*
** VelocityMeasurement
*/
void BVelocityMeasurement(void)
{
	//g_i16LastLeftVal=g_i16LastLeftVal;
	//g_i16LastRightVal=g_i16RightVal;
        g_iLastAverageSpeed = g_iAverageSpeed;

	//g_i16LeftVal = DMA_count_get(DMA_CH2);
	//DMA_count_reset(DMA_CH2);
	
	g_iAverageSpeed=FTM_QUAD_get(COUNTER1_FTM);
	FTM_QUAD_clean(COUNTER1_FTM);
    g_iAverageSpeed=(int)(g_iAverageSpeed/5);
    
    if((g_iAverageSpeed>=10) && (g_iAverageSpeed<=20))
      {
        g_iVCount1+=1;
        if(g_iVCount1 >= 30)
        {
          g_iStableGrade15 = 1;
          g_iVCount1=0;
          LedControl(3);
        }
      }
    else
      if((g_iAverageSpeed>=40) && (g_iAverageSpeed<=50))
      {
        g_iVCount2+=1;
        if(g_iVCount2 >= 30)
        {
          g_iStableGrade45 = 1;
          g_iVCount2=0;
          LedControl(3);
        }
      }
    else
      if((g_iAverageSpeed>=50) && (g_iAverageSpeed<=70))
      {
        g_iVCount3+=1;
        if(g_iVCount3 >= 3)
        {
          g_iStableGrade75 = 1;
          g_iVCount3=0;
          LedControl(3);
        }
      }
    else
      if((g_iAverageSpeed>=100) && (g_iAverageSpeed<=110))
      {
        g_iVCount4+=1;
        if(g_iVCount4 >= 30)
        {
          g_iStableGrade105 = 1;
          g_iVCount4=0;
          LedControl(3);
        }
      }
   
    if( g_iAverageSpeed >10)
    {
      g_iProtectMotor =1;
    }
    
    if(g_iProtectMotor == 1)
    {
      if(g_iAverageSpeed <= 5)
      {
        g_iProtectFlag +=1;
        if(g_iProtectFlag >=10)
        {
          g_iStopMotor = 1;
        }
       }
    }
   
}

void CVelocityMeasurement(void)
{
  g_i16LastRightVal=g_i16RightVal;
  g_i16LastLeftVal=g_i16LeftVal;
  
  g_i16LeftVal =FTM_QUAD_get(COUNTER1_FTM);
  FTM_QUAD_clean(COUNTER1_FTM);
  
  g_i16RightVal = DMA_count_get(DMA_CH2);
  DMA_count_reset(DMA_CH2);

 
 if((gpio_get (PTE2)) == 1)
  {
	g_i16RightVal = -g_i16RightVal;			 
  }
 

  g_iAverageSpeed= (g_i16RightVal+ g_i16LeftVal)/2;
}

void DMA_CH2_Handler(void)
{
	DMA_IRQ_CLEAN(DMA_CH2);                            
	DMA_EN(DMA_CH2);                                  
}

void AverageSpeedCalculation(void)
{
	g_iAverageSpeed=(g_i16LeftVal+g_i16RightVal)/2;
}
