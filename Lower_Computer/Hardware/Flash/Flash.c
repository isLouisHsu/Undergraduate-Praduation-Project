#include "Flash.h"

void FlashInit(int FlashNumber)
{
	int i,k;
	for(i =200;i <FlashNumber;i++)
	{
		flash_erase_sector(i);
	}
        g_u32SpeedP  =(uint32)g_fSpeedP;
        g_u32SpeedI  =(uint32)g_fSpeedI;
        g_u32SpeedD  =(uint32)(g_fSpeedD*10);
        
	flash_write(200, 0, g_u32SpeedP);	
	flash_write(201, 0, g_u32SpeedI);	
	flash_write(202, 0, g_u32SpeedD);	
	flash_write(203, 0, g_iSpeedSet);	

	/*for(i=204,k=0;k<20;k++)
	{
		flash_write(i+k, 0, g_u8TopL[k]);	
	}
	for(i=224,k=0;k<20;k++)
	{
		flash_write(i+k, 0, g_u8TopR[k]);	
	}
	*/
}


void FlashRead(void)
{
  g_u32SpeedP=flash_read(200,0,uint32);
  g_u32SpeedI=flash_read(201,0,uint32);
  g_u32SpeedD=flash_read(202,0,uint32);
  g_iSpeedSet=flash_read(203,0,uint16);
}
void FlashWrite(void)
{
  int i,j;
	//Steer
	g_iSteeringMid=flash_read(200,0,uint32);
	DELAY_MS(5);
	g_iSteeringLeft=flash_read(201,0,uint32);
	DELAY_MS(5);
	g_iSteeringRight=flash_read(202,0,uint32);
	DELAY_MS(5);
/*	g_fSteeringP=flash_read(203,0,float);
	DELAY_MS(5);
	g_fSteeringI=flash_read(204,0,float);
	DELAY_MS(5);
	g_fSteeringD=flash_read(205,0,float);
	DELAY_MS(5);*/

	//Motor
	g_iSpeedSet=flash_read(206,0,uint32);
	DELAY_MS(5);
	/*g_fSpeedP=flash_read(207,0,float);
	DELAY_MS(5);
	g_fSpeedI=flash_read(208,0,float);
	DELAY_MS(5);
	g_fSpeedD=flash_read(209,0,float);
	DELAY_MS(5);*/

	//g_u8TopL
	for(i=204,j=0;j<20;j++)
	{
		g_u8TopL[j]=flash_read(i+j,0,uint8);
		DELAY_MS(5);
	}
	//g_u8TopR
	for(i=224,j=0;j<20;j++)
	{
		g_u8TopR[j]=flash_read(i+j,0,uint8);
		DELAY_MS(5);
	}
}