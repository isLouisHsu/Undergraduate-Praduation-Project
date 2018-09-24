#include "datatranslate.h"

uint8 Data_Check,Send_Status,Send_Senser,Send_Offset,Send_PID1,Send_PID2,Send_PID3,Send_PID4,Send_PID5,Send_PID6;
uint8 data_to_send[50];


int g_iFlagStart = 0;

static unsigned char RxBuffer[50];
static unsigned char RxState = 0;


float P1 = 1;
//Lower computer analytic upper computer
void Data_Receive_Anl(uint8 *data_buf,uint8 num)
{															
	uint8 sum = 0;
	uint8 i=0;
	for(i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		
		return;		//judge sum
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		
		return;		//Frame header

	if(*(data_buf+2)==0X01)
	{
		if(*(data_buf+4)==0X01)
//			MPU6050_CalOff_Acc();				//original:Correction of accelerometer
            g_iFlagStart = 1;
		if(*(data_buf+4)==0X02)
//			MPU6050_CalOff_Gyr();				//original:Gyro rectification
            g_iFlagStart = 0;
//		if(*(data_buf+4)==0X03)
//		{MPU6050_CalOff_Acc();MPU6050_CalOff_Gyr();}

		if(*(data_buf+4)==0X04)					//original:	Correction of magnetic force meter
//			Cal_Compass();					
			 g_iSpeed +=30;					
		if(*(data_buf+4)==0X05)
//			MS5611_CalOffset();					//Correction of pressure gauge
			 g_iSpeed -=30;					
	}
	if(*(data_buf+2)==0X02)
	{
		if(*(data_buf+4)==0X01)					//Read the flight
		{
			Send_PID1 = 1;
			Send_PID2 = 1;
			Send_PID3 = 1;
			Send_PID4 = 1;
			Send_PID5 = 1;
			Send_PID6 = 1;
		}
		if(*(data_buf+4)==0X02)
			Send_Offset = 1;
		}																
	if(*(data_buf+2)==0X10)			      //Send PID1 (1~3)									
	{
			P1 = (float)((unsigned int)(*(data_buf+4)<<8)|*(data_buf+5));		
			P1 = (float)((unsigned int)(*(data_buf+6)<<8)|*(data_buf+7));
			P1 = (float)((unsigned int)(*(data_buf+8)<<8)|*(data_buf+9));
			P1 = (float)((unsigned int)(*(data_buf+10)<<8)|*(data_buf+11));		
			P1 = (float)((unsigned int)(*(data_buf+12)<<8)|*(data_buf+13))/10;
			P1 = (float)((unsigned int)(*(data_buf+14)<<8)|*(data_buf+15))/100;
			P1 = (float)((unsigned int)(*(data_buf+16)<<8)|*(data_buf+17));		
			P1 = (float)((unsigned int)(*(data_buf+18)<<8)|*(data_buf+19))/100;
			P1 = (float)((unsigned int)(*(data_buf+20)<<8)|*(data_buf+21))/100;
			Data_Send_Check(sum);
	}
	if(*(data_buf+2)==0X11)								//Send PID2(4~6)
	{
			P1 = (float)((unsigned int)(*(data_buf+4)<<8)|*(data_buf+5))/100;		//ALT
			P1 = (float)((unsigned int)(*(data_buf+6)<<8)|*(data_buf+7))/100;
			P1 = (float)((unsigned int)(*(data_buf+8)<<8)|*(data_buf+9))/100;
			P1 = (float)((unsigned int)(*(data_buf+10)<<8)|*(data_buf+11))/100;		//POS
			P1 = (float)((unsigned int)(*(data_buf+12)<<8)|*(data_buf+13))/100;
			P1 = (float)((unsigned int)(*(data_buf+14)<<8)|*(data_buf+15))/100;
			P1 = (float)((unsigned int)(*(data_buf+16)<<8)|*(data_buf+17))/100;	//ÄÚ»·PITCH
			P1 = (float)((unsigned int)(*(data_buf+18)<<8)|*(data_buf+19))/100;
			P1 = (float)((unsigned int)(*(data_buf+20)<<8)|*(data_buf+21))/100;
			Data_Send_Check(sum);
	}
		if(*(data_buf+2)==0X12)								//Send PID3(7~9)
	{
			g_fSpeedP = (float)((unsigned int)(*(data_buf+4)<<8)|*(data_buf+5))/100;		
			g_fSpeedI = (float)((unsigned int)(*(data_buf+6)<<8)|*(data_buf+7))/1000;
			g_fSpeedD = (float)((unsigned int)(*(data_buf+8)<<8)|*(data_buf+9))/10000;
			g_fSteeringP = (float)((unsigned int)(*(data_buf+10)<<8)|*(data_buf+11))/100;	
			g_fSteeringI = (float)((unsigned int)(*(data_buf+12)<<8)|*(data_buf+13))/1000;
			g_fSteeringD = (float)((unsigned int)(*(data_buf+14)<<8)|*(data_buf+15))/10000;
			P1 = (float)((unsigned int)(*(data_buf+16)<<8)|*(data_buf+17))/100;	
			P1= (float)((unsigned int)(*(data_buf+18)<<8)|*(data_buf+19))/1000;
			P1 = (float)((unsigned int)(*(data_buf+20)<<8)|*(data_buf+21))/10000;
			Data_Send_Check(sum);
	}
	if(*(data_buf+2)==0X13)								//PID4(10-12)				//Ã»ÓÃµ½
	{
			P1 = (float)((unsigned int)(*(data_buf+4)<<8)|*(data_buf+5))/1000;
			P1 = (float)((unsigned int)(*(data_buf+8)<<8)|*(data_buf+9))/100000;
			P1 = (float)((unsigned int)(*(data_buf+10)<<8)|*(data_buf+11))/1000;
			P1 = (float)((unsigned int)(*(data_buf+12)<<8)|*(data_buf+13))/1000;
			P1 = (float)((unsigned int)(*(data_buf+14)<<8)|*(data_buf+15))/100000;
			P1 = (float)((unsigned int)(*(data_buf+16)<<8)|*(data_buf+17))/1000;
			P1 = (float)((unsigned int)(*(data_buf+18)<<8)|*(data_buf+19))/1000;
			P1 = (float)((unsigned int)(*(data_buf+20)<<8)|*(data_buf+21))/100000;
			Data_Send_Check(sum);
	}
	if(*(data_buf+2)==0X14)								//PID5(13-15)	Ã»ÓÃµ½
	{
			P1 = (float)((unsigned int)(*(data_buf+4)<<8)|*(data_buf+5))/1000;
			P1 = (float)((unsigned int)(*(data_buf+6)<<8)|*(data_buf+7))/1000;
			P1 = (float)((unsigned int)(*(data_buf+8)<<8)|*(data_buf+9))/100000;
			P1 = (float)((unsigned int)(*(data_buf+10)<<8)|*(data_buf+11))/1000;
			P1 = (float)((unsigned int)(*(data_buf+12)<<8)|*(data_buf+13))/1000;
			P1 = (float)((unsigned int)(*(data_buf+14)<<8)|*(data_buf+15))/100000;
			P1 = (float)((unsigned int)(*(data_buf+16)<<8)|*(data_buf+17))/1000;
			P1 = (float)((unsigned int)(*(data_buf+18)<<8)|*(data_buf+19))/1000;
			P1 = (float)((unsigned int)(*(data_buf+20)<<8)|*(data_buf+21))/100000;
			Data_Send_Check(sum);
	}
	if(*(data_buf+2)==0X15)								//PID6(16-17)	Ã»ÓÃµ½
	{
			P1 = (float)((unsigned int)(*(data_buf+4)<<8)|*(data_buf+5))/1000;
			P1 = (float)((unsigned int)(*(data_buf+6)<<8)|*(data_buf+7))/10000;
			P1 = (float)((unsigned int)(*(data_buf+8)<<8)|*(data_buf+9))/100000;
			P1 = (float)((unsigned int)(*(data_buf+10)<<8)|*(data_buf+11))/1000;
			P1 = (float)((unsigned int)(*(data_buf+12)<<8)|*(data_buf+13))/10000;
			P1 = (float)((unsigned int)(*(data_buf+14)<<8)|*(data_buf+15))/100000;
			Data_Send_Check(sum);
	}
//	if(*(data_buf+2)==0X16)								//OFFSET
//	{
//		AngleOffset_Rol = (float)((int16)(*(data_buf+4)<<8)|*(data_buf+5))/1000;
//		AngleOffset_Pit = (float)((int16)(*(data_buf+6)<<8)|*(data_buf+7))/1000;	
//	}
}

/*
Send Motor
*/
void Data_Send_MotoPWM(void)
{
	uint8 _cnt=0;
	uint8 sum = 0;
	uint8 i=0;
    int temp = 0;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x06;
	data_to_send[_cnt++]=0;
    
    temp = (int)g_iSteeringValue;
	data_to_send[_cnt++]=BYTE1(temp);             //LNG    //M1
	data_to_send[_cnt++]=BYTE0(temp);
    
    temp= g_iAverageSpeed;
	data_to_send[_cnt++]=BYTE1(temp);  //MOTOR1    //M2
	data_to_send[_cnt++]=BYTE0(temp);
     
    temp =g_iAverageSpeed; 
	data_to_send[_cnt++]=BYTE1( temp);  //MOTOR2    //M3
	data_to_send[_cnt++]=BYTE0( temp); 
    
    temp =g_iAverageSpeed; 
	data_to_send[_cnt++]=BYTE1( temp);  //MOTOR3   //M4
	data_to_send[_cnt++]=BYTE0( temp);
    
   
	/*data_to_send[_cnt++]=BYTE1(g_iLastAverageSpeed);
	data_to_send[_cnt++]=BYTE0(g_iLastAverageSpeed); 
	data_to_send[_cnt++]=BYTE1(g_iLastAverageSpeed);  
	data_to_send[_cnt++]=BYTE0(g_iLastAverageSpeed);
    
    data_to_send[_cnt++]=BYTE1(g_iLastAverageSpeed);    //MOTOR1
	data_to_send[_cnt++]=BYTE0(g_iLastAverageSpeed);
	data_to_send[_cnt++]=BYTE1(g_iLastAverageSpeed);    //MOTOR1
	data_to_send[_cnt++]=BYTE0(g_iLastAverageSpeed);
	*/
	
	data_to_send[3] = _cnt-4;

	for( i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	uart_putbuff (UART4,data_to_send,_cnt);
}

/*
Send sensor value
*/
void Data_Send_Senser(void)								
{																   
	uint8 _cnt=0;
	uint8 sum = 0;
	uint8 i=0;
        uint8 temp;
    
    //temp = g_u8Top1;
 
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
 
    //temp = g_u8Top1;
	data_to_send[_cnt++]=BYTE1(temp);  				
	data_to_send[_cnt++]=BYTE0(temp);  
    
    //temp = g_u8Top2;
	data_to_send[_cnt++]=BYTE1(temp);  				
	data_to_send[_cnt++]=BYTE0(temp); 
 	
    //temp = g_u8Top3;
	data_to_send[_cnt++]=BYTE1(temp);  				
	data_to_send[_cnt++]=BYTE0(temp);  
    
    //temp = g_u8Top4;
	data_to_send[_cnt++]=BYTE1(temp);
	data_to_send[_cnt++]=BYTE0(temp);
    
    //temp = g_u8Top5;
	data_to_send[_cnt++]=BYTE1(temp);
	data_to_send[_cnt++]=BYTE0(temp);
    
    //temp = g_u8Top;
	data_to_send[_cnt++]=BYTE1(temp);
	data_to_send[_cnt++]=BYTE0(temp);
    
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	
	data_to_send[3] = _cnt-4;

	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;

	uart_putbuff (UART4,data_to_send,_cnt);
}

/*
void Data_Send_Status(void)								
{
	uint8 _cnt=0;
	int16 _temp;
	uint8 sum = 0;
	uint8 i=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;

	_temp = (int)(Att_Angle.rol*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(Att_Angle.pit*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(Att_Angle.yaw*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
		
	data_to_send[_cnt++]=0xA1;
	
	data_to_send[3] = _cnt-4;

	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;

	uart_putbuff (UART4,data_to_send,_cnt);
}
*/

void Data_Send_PID1(void)				
{																		
	uint8 _cnt=0;
	int16 _temp;
	uint8 sum = 0;
	uint8 i=0;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x10;
	data_to_send[_cnt++]=0;
	
	_temp = g_iSpeed* 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	uart_putbuff (UART4,data_to_send,_cnt);
}

void Data_Send_PID2(void)										
{
	uint8 _cnt=0;
	int16 _temp;
	uint8 sum = 0;
	uint8 i=0;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x11;
	data_to_send[_cnt++]=0;

	_temp =g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	_temp = g_iSpeed* 100;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	_temp = g_iSpeed* 100;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_iSpeed * 100;

	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;

	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	uart_putbuff (UART4,data_to_send,_cnt);
}

void Data_Send_PID3(void)								
{
	uint8 _cnt=0;
	int16 _temp;
	uint8 sum = 0;
	uint8 i=0;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x12;
	data_to_send[_cnt++]=0;
	
	_temp = g_fSpeedP * 100;			//PID2 P 					
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_fSpeedI * 100;            //PID2 I
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_fSpeedD * 100;            //PID2 D
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_fSteeringP * 100;         //PID3 P 
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_fSteeringI * 100;         //PID3 I
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_fSteeringD * 100;         //PID3 D
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_fSpeedP * 100;     
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_fSpeedI * 100;
 	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_fSpeedD * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;

	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	uart_putbuff (UART4,data_to_send,_cnt);
}

void Data_Send_Check(uint16 check)						
{																			
	uint8 sum = 0;
	uint8 i=0;
	data_to_send[0]=0xAA;
	data_to_send[1]=0xAA;
	data_to_send[2]=0xF0;
	data_to_send[3]=3;
	data_to_send[4]=0xBA;
	
	data_to_send[5]=BYTE1(check);
	data_to_send[6]=BYTE0(check);

	for(i=0;i<7;i++)
		sum += data_to_send[i];
	
	data_to_send[7]=sum;

	/*for(i=0;i<8;i++)
    {
        uart_putchar(UART4, data_to_send[i]);
    }
*/
	uart_putbuff (UART4,data_to_send,8);
}


void Data_Receive(unsigned char com_data)
{
  static unsigned char _data_len = 0,_data_cnt = 0;
  if(RxState==0&&com_data==0xAA)
  {
          RxState=1;
          RxBuffer[0]=com_data;
  }
  else if(RxState==1&&com_data==0xAF)
  {
          RxState=2;
          RxBuffer[1]=com_data;
  }
  else if(RxState==2&&com_data>0&&com_data<0XF1)
  {
          RxState=3;
          RxBuffer[2]=com_data;
  }
  else if(RxState==3&&com_data<50)
  {
          RxState = 4;
          RxBuffer[3]=com_data;
          _data_len = com_data;
          _data_cnt = 0;
  }
  else if(RxState==4&&_data_len>0)
  {
          _data_len--;
          RxBuffer[4+_data_cnt++]=com_data;
          if(_data_len==0)
                  RxState = 5;
  }
  else if(RxState==5)
  {
          RxState = 0;
          RxBuffer[4+_data_cnt]=com_data;
          Data_Receive_Anl(RxBuffer,_data_cnt+5);
  }
  else
          RxState = 0;
}


