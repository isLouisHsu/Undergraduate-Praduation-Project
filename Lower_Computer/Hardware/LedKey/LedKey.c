#include "LedKey.h"

uint8 switch_sta=0;
int g_ichoice = 0;
int g_ichoiceShow = 0;
int g_ichoiceMotor = 0;
int g_ichoiceSteer = 0;
int g_ichoiceTopL = 0;
int g_iKeyValue = 0;
//unsigned char oled_picture[1024];

/*
**LED KEY DIAL IO Init
LED0:PTC0;LED1:PTE24;LED2:25;LED3:PTE26;LED4:PTE27;LED5:PTE28
IO1:PTE3;IO2:PTE4;IO3:PTE5
KEY1:PTE6;KEY2:PTE7;KEY3:PTE8
DIAL1:PTE9;DIAL2:PTE10;DIAL3:PTE11
*/
void IoLedKeyDialInit(void)
{
	uint8 nLed,nKey;

	gpio_init(PTC1,GPO,0);
	gpio_init(PTA17, GPO, 1);
	gpio_init(PTD15,GPO,0);
        gpio_init(PTD2,GPO,0);
     
	gpio_init(PTE2,GPI,0);
           gpio_init(PTE3,GPO,1);
	
	for(nLed = 0;nLed<5;nLed++)			//led
	{
		gpio_init((PTXn_e)(PTE24+nLed),GPO,1);
	}

	for(nKey = 0;nKey<8;nKey++)			//io,key,dial
	{
		gpio_init((PTXn_e)(PTE4+nKey),GPI,1);
	}
}

void LedControl(int x)
{
	if(x == 0)
	{
	  gpio_set(PTE24,0);
	  gpio_set(PTE25,0);
	  gpio_set(PTE26,0);
	  gpio_set(PTE27,0);
	  gpio_set(PTE28,0);
	}
	else
		if(x == 1)
		{
			 gpio_set(PTE24,1);
			 gpio_set(PTE28,1);
		}
		else
			if(x == 2)
			{
				gpio_set(PTE25,1);
				gpio_set(PTE27,1);
			}
			else
				if(x == 3)
				{
					gpio_set(PTE26,1);
				}
				else
                  if(x == 4)
                  {
                    gpio_set(PTE24,1);
                    gpio_set(PTE25,1);
                    gpio_set(PTE26,1);
                    gpio_set(PTE27,1);
                    gpio_set(PTE28,1);
                  }			
}

uint8 Switch()
{
  	uint8 Value=0;
	
	if(gpio_get (PTE11)==0) 
	    Value =Value+4;
    if(gpio_get (PTE10)==0)     
        Value=Value+2;
    if(gpio_get (PTE9)==0) 
        Value=Value+1;

	return Value;
}

void OledShow(void)
{
        static uint8 cntL=0;
        static uint8 cntR=0;
        static uint8 cntDir=0;
        
        switch_sta = Switch();
	switch(switch_sta)
	{
		case 1:/* 显示左右、平均、设定速度值 */
                        KeyScan();
                        OLED_Print(1,0,"LV"); 
                        OLED_Print(1,2,"RV"); 
                        OLED_Print(1,4,"AV");
                        OLED_Print(1,6,"SV");
                        Oled_display_large(g_i16LeftVal,g_i16RightVal,g_iAverageSpeed,g_iSpeedSet);
                        
                        if(g_iKeyValue == 1)      g_iSpeedSet +=15.00;
                        else if(g_iKeyValue == -1)g_iSpeedSet -=15.00;
                        g_iKeyValue = 0;
                        break;
                case 2:/* 左边距离调整 */
                       KeyScan();
                       
                       if(g_iKeyValue == 2){g_ichoiceSteer+=1;if( g_ichoiceSteer > 1)g_ichoiceSteer=0;}
                       
                       if(g_ichoiceSteer==0)
                       {
                         OLED_Print(7,2,"*");
                         OLED_Print(7,4," ");
                         if(g_iKeyValue == 1 && cntL<20)     cntL+=1;
                         else if(g_iKeyValue == -1 && cntL>0)cntL-=1;
                       }
                       else if(g_ichoiceSteer==1)
                       {
                         OLED_Print(7,2," ");
                         OLED_Print(7,4,"*");
                         if(g_iKeyValue == 1)      g_u8TopL[cntL]+=1;
                         else if(g_iKeyValue == -1)g_u8TopL[cntL]-=1;
                       }
                       
                       OLED_Print(1,0,"LT");
                       //OLED_Print(1,2,"CNT");
                       //OLED_Print(1,4,"DST");
                       Oled_display_large(0,cntL,g_u8TopL[cntL],g_ichoiceSteer);
                        
                       g_iKeyValue = 0;
                       break;                        
                case 3:/* 右边距离调整 */
                       KeyScan();
                       
                       if(g_iKeyValue == 2){g_ichoiceSteer+=1;if( g_ichoiceSteer > 1)g_ichoiceSteer=0;}
                       
                       if(g_ichoiceSteer==0)
                       {
                         OLED_Print(7,2,"*");
                         OLED_Print(7,4," ");
                         if(g_iKeyValue == 1 && cntR<20)     cntR+=1;
                         else if(g_iKeyValue == -1 && cntR>0)cntR-=1;
                       }
                       else if(g_ichoiceSteer==1)
                       {
                         OLED_Print(7,2," ");
                         OLED_Print(7,4,"*");
                         if(g_iKeyValue == 1)      g_u8TopR[cntR]+=1;
                         else if(g_iKeyValue == -1)g_u8TopR[cntR]-=1;
                       }
                       
                       OLED_Print(1,0,"RT");
                       //OLED_Print(1,2,"CNT");
                       //OLED_Print(1,4,"DST");
                       Oled_display_large(0,cntR,g_u8TopR[cntR],g_ichoiceSteer);
                        
                       g_iKeyValue = 0;
                       break;  
                case 4:/* 策略 */
                       KeyScan();
                       
                       if(g_iKeyValue == 2){g_ichoiceSteer+=1;if( g_ichoiceSteer > 1)g_ichoiceSteer=0;}
                       
                       if(g_ichoiceSteer==0)
                       {
                         OLED_Print(7,2,"*");
                         OLED_Print(7,4," ");
                         if(g_iKeyValue == 1 && cntDir<10)     cntDir+=1;
                         else if(g_iKeyValue == -1 && cntDir>0)cntDir-=1;
                       }
                       else if(g_ichoiceSteer==1)
                       {
                         OLED_Print(7,2," ");
                         OLED_Print(7,4,"*");
                         if(g_iKeyValue == 1)      g_u8TurnDir[cntDir]=!g_u8TurnDir[cntDir];
                       }
                       
                       OLED_Print(1,0,"Dir");
                       
                       Oled_display_large(0,cntDir+1,g_u8TurnDir[cntDir],g_ichoiceSteer);
                        
                       g_iKeyValue = 0;
                       break;  
             case 5:
                 break;
             case 6:KeyScan();
                       if(g_iKeyValue == 2)
                       {
                         g_ichoiceSteer+=1;
                         if( g_ichoiceSteer > 3)
                         {
                            g_ichoiceSteer=0;
                         }
                       }
                       //g_iSteeringMid
                        if(g_iKeyValue == 1 &&  g_ichoiceSteer == 0)
                        {
                          g_iSteeringMid +=1;
                          SteeringPwm(g_iSteeringMid);
                        }
                        else
                          if(g_iKeyValue == -1 && g_ichoiceSteer == 0)
                          {
                            g_iSteeringMid -=1;
                          SteeringPwm(g_iSteeringMid);
                          }
                       //P
                         if(g_iKeyValue == 1 && g_ichoiceSteer == 1)
                        {
                         g_fSteeringP+=0.01;
                        }
                        else
                          if(g_iKeyValue == -1 && g_ichoiceSteer == 1)
                          {
                            g_fSteeringP-=0.01;
                          }
                       //I
                        if(g_iKeyValue == 1 && g_ichoiceSteer == 2)
                        {
                         g_fSteeringI+=0.01;
                        }
                        else
                          if(g_iKeyValue == -1 && g_ichoiceSteer == 2)
                          {
                            g_fSteeringI-=0.01;
                          }
                       //D
                         if(g_iKeyValue == 1 && g_ichoiceMotor == 3)
                        {
                         g_fSteeringD+=0.01;
                        }
                        else
                          if(g_iKeyValue == -1 && g_ichoiceSteer == 3)
                          {
                            g_fSteeringD-=0.01;
                          }
                       //show
                       if(g_ichoiceSteer == 0)
                       {
                         OLED_Print(1,0,"SV");
		         OLED_Print(1,2,"SM"); 
		         OLED_Print(1,4,"SL"); 
		         OLED_Print(1,6,"SR");
                         Oled_display_large(g_iSteeringValue,g_iSteeringMid,g_iSteeringLeft,g_iSteeringRight);
                       }
                       else
                         if(g_ichoiceSteer != 0)
                         {
                            OLED_Print(1,0,"SP");
                            OLED_Print(1,2,"SI");
                            OLED_Print(1,4,"SD");
                            OLED_Print(1,6,"SC");
                            Oled_display_large(g_fSteeringP,g_fSteeringI,g_fSteeringD,g_ichoiceSteer);
                         }
                       g_iKeyValue = 0;
                    break;
       
              default:break;
        }
}

void KeyScan(void)
{
  int s1,s2,s3;
  
  s1=gpio_get(PTE6);  //up
  s2=gpio_get(PTE7); 
  s3=gpio_get(PTE8);  //down
   
  if(s1 == 0)
  {
    DELAY_MS(120);
    if(s1 == 0)
    {
      g_iKeyValue = 1;
    }
  }
  else
    if(s3 == 0)
  {
    DELAY_MS(120);
    if(s3 == 0)
    {
      g_iKeyValue = -1;
    }
  }
   else
    if(s2 == 0)
  {
    DELAY_MS(120);
    if(s2 == 0)
    {
      g_iKeyValue = 2;
    }
  }
}

void TopLParameterAdjustment(void)
{
  if(g_ichoiceTopL == 0)
  {
    KeyScan();
    if( g_iKeyValue == 1)
      g_u8TopL[0]+=1;
    else
     if( g_iKeyValue == -1)
        g_u8TopL[0]-=1;
  }
  else
    if(g_ichoiceTopL == 1)
    {
       KeyScan();
    if( g_iKeyValue == 1)
      g_u8TopL[1]+=1;
    else
     if( g_iKeyValue == -1)
        g_u8TopL[1]-=1;
    }
   else
    if(g_ichoiceTopL == 2)
    {
       KeyScan();
    if( g_iKeyValue == 1)
      g_u8TopL[2]+=1;
    else
     if( g_iKeyValue == -1)
        g_u8TopL[2]-=1;
    }
   else
    if(g_ichoiceTopL == 3)
    {
       KeyScan();
    if( g_iKeyValue == 1)
      g_u8TopL[3]+=1;
    else
     if( g_iKeyValue == -1)
        g_u8TopL[3]-=1;
    }
}
