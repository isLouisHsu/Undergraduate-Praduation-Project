#include "predatorcamera.h"

int g_iLineIrq = 0;		//line interrupt
int g_iSeparate = 0;
int g_iLine = 0; 
int g_iRealLine = 0;

uint8 u8_PredatorCameraBuffer[LINE][COLUMN]={0};     		//Array of images to be original
uint8 u8_PendingTreatmentBuffer[LINE][COLUMN]={0};  //Array of images to be processed
uint8 u8_FinishProcessingBuffer[LINE][COLUMN]={0}; 	//Array of images to be finish
 
 /***************Predator Camera***************/

void PredatorCameraInit(void)
{
	/*
	**Camera IO:data,line site interrupt
	*/
	gpio_init(CAM1_Y0, GPI, 0);  		
	gpio_init(CAM1_Y1, GPI, 0); 
	gpio_init(CAM1_Y2, GPI, 0); 
	gpio_init(CAM1_Y3, GPI, 0); 
	gpio_init(CAM1_Y4, GPI, 0); 
	gpio_init(CAM1_Y5, GPI, 0); 
	gpio_init(CAM1_Y6, GPI, 0);  
	gpio_init(CAM1_Y7, GPI, 0); 
	gpio_init(CAM1_FODD, GPI, 0);
	gpio_init(CAM1_PCLK, GPI, 0);

	port_init(CAM1_HREF,  ALT1 | IRQ_RISING  | PULLDOWN);	
	port_init(CAM1_VSYNC, ALT1 | IRQ_FALLING | PULLUP);

	set_vector_handler(PORTD_VECTORn, PORTD_IRQHandler);  //site interrupt:D port
	set_vector_handler(DMA1_VECTORn,  DMA_CH1_Handler); //line interrupt:DMA1_CH1

	dma_portx2buff_init(DMA_CH1, &PTE_B0_IN,u8_PredatorCameraBuffer[0], CAM1_PCLK, DMA_BYTE1,COLUMN, DADDR_KEEPON); 	
	//EN interrupt	
	DMA_DIS(DMA_CH1);
	DMA_IRQ_DIS(DMA_CH1);
	enable_irq (PORTD_IRQn); 
	EnableInterrupts;
}	

/*
**camera1 D interrupt
*/
void PORTD_IRQHandler(void)
{
	//line interrupt
	if(g_iLineIrq == 1)
	{
		if(PORTD_ISFR & (1 <<13 ))
		{
			PORTD_ISFR  |= (1 << 13); 
			g_iLine++;

			if(g_iLine<=60)
			 g_iSeparate=6;//10
			else
			 if(g_iLine>60&&g_iLine<180)
			  g_iSeparate=4;//30
			  else
			   g_iSeparate=7;//20

			if((g_iLine % g_iSeparate == 0) &&(g_iLine<480))
			{		// æ¯éš”Nè¡Œï¼Œé‡‡ä¸€è¡?if((line %(480/H) == 0) &&(LinADCout<H))	
				DMA_DADDR(DMA_CH1) = (uint32)u8_PredatorCameraBuffer[g_iRealLine] ;   //æ•°æ®å­˜å‚¨åœ°å€å˜åŒ�?				DMA_EN(DMA_CH1);
				DMA_IRQ_EN(DMA_CH1);	
			}	
		}
	}
	/*
	**field interrupt
	*/
	else
	  if(PORTD_ISFR & (1 << 14))
	  {
	  	PORTD_ISFR  |= (1 << 14);        

	  	gpio_turn(PTC10);				 //work indicator light
		g_iLine = 0;                     //line clear
		g_iRealLine = 0;                
		g_iJudege++;					
			
		if(g_iJudege==2)
		{	
			g_iJudege=0;
			g_iLineIrq=0;     	//line interrput
			g_iMain = 1;
            
			disable_irq(PTD); 
		}
		else
		 g_iLineIrq = 1;  		//ongoing line interrupt

		 PORTD_ISFR  |= (1 << 13);   
		}
}

/*
**camera1 DMA_CH1
*/
void DMA_CH1_Handler(void)
{
	DMA_IRQ_CLEAN(DMA_CH1); 	   
	DMA_DIS(DMA_CH1); 					

	g_iRealLine++;			 //Actual number of rows

	if(g_iRealLine == LINE)
	{ 	  
		g_iRealLine=0;
		g_iLineIrq = 0;		
		g_iLine = 0;

		DMA_DIS(DMA_CH1);
		DMA_IRQ_DIS(DMA_CH1);
		memcpy(u8_PendingTreatmentBuffer, u8_PredatorCameraBuffer, LINE*COLUMN);
		PORTD_ISFR  |= (1 << 14); 	   
		PORTD_ISFR  |= (1 << 13); 	  
	}
}

