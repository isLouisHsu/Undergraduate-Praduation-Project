#include "bluetooth.h"

uint16 BlueTeeth[6];	
uint8  BlueTeeth2[50];

uint8  RxData[10]={0};
uint8  rxsta = 0;
uint8  StartMove = 0;
uint8  Received = 0;
uint8  ReceiveEnable = 1;
uint8  BlueToothSent = 0;

//int16 RxAngle = 0,RxAngleLast = 0;
//int16 RxSpeedLeft = 0,RxSpeedRight = 0;

uint8 RxAngle = 0;      //接收到的角度大小
uint8 RxDirAngle = 0;   //接收到的角度方向
uint8 RxDirSpeed = 0;   //接收到的速度方向
uint16 RxSpeed = 0;     //接收到的速度大小

int16 RxIntAngle = 0;   //处理后的角度，包括方向信息
int16 RxIntAnglelast = 0;   //处理后的角度，包括方向信息
int16 RxIntSpeed = 0;   //处理后的速度，包括方向信息
uint8 RxIsInsight=0;    //是否在视野内,'1'在视野内,'0'表示在视野外
uint16 RxDistance = 0;

void bluetoothSent(uint8 LeftOrRight, uint8 top, int speed)
{
  if(BlueToothSent==0)
  {
    printf("dir: %d, dist: %d, speed: %d\n", LeftOrRight, top, speed);
    BlueToothSent = 1;
  }
}

void BluetoothInit(int BTbaudrate)
{
   uart_init(BT_UART, BTbaudrate);						//baud rate:115200
   
   set_vector_handler(UART4_RX_TX_VECTORn, uart4_handler);
   uart_rx_irq_en(UART4);
   NVIC_SetPriority(UART4_RX_TX_VECTORn,2);
}

//bluetooth interrupt
void uart4_handler(void)
{
  char ch;
  UARTn_e uratn = UART4;
  
#if 1
  if(UART_S1_REG(UARTN[uratn]) & UART_S1_RDRF_MASK)
  {
    uart_getchar(UART4, &ch);
    if(rxsta==0 && ch==0x5a)
    {
      rxsta = 1;
    }
    else if(rxsta==1)
    {
      RxData[0] = ch;
      rxsta = 2;
    }
    else if(rxsta==2)
    {
      RxData[1] = ch;
      rxsta = 3;
    }
    else if(rxsta==3)
    {
      RxData[2] = ch;
      rxsta = 4;
    }
    else if(rxsta==4)
    {
      RxData[3] = ch;
      rxsta = 5;
    }
    else if(rxsta==5)
    {
      RxData[4] = ch;
      rxsta = 6;
    }
    else if(rxsta==6)
    {
      RxData[5] = ch;
      rxsta = 7;
    }
    else if(rxsta==7 && ch=='a')
    {
      Received = 1;
      rxsta = 0;
	  gpio_turn(PTD15);
    }
    else
    {
      rxsta = 0;
    }
    
  }
  if(UART_S1_REG(UARTN[uratn]) & UART_S1_TDRE_MASK )
  {
  }
#endif
}

/******************monlie phone BT*******************/
void extern_event_process(void)  
{
  if(frame_ready == TRUE)
  {
    int param = 1;
    //uart_putchar(UART4, 0x88);
    switch(frame[0])
    {
    case UART_SLIDE1: 
      break;
      
    case UART_SLIDE2: 
      break;
      
    case UART_SLIDE3: 
      break;
      
    case UART_KEY1: 
      gpio_turn(PTA14);
      // g_fSteerKP += 0.5;
      break;
      
    case UART_KEY2:
      gpio_turn(PTA14);
      //  g_fSteerKP -= 0.5;
      break;
      
    case UART_KEY3: 
      gpio_turn(PTA14);
      // PWMSet += 10;
      break;
      
    case UART_KEY4: 
      gpio_turn(PTA14);
      // PWMSet -= 10;
      break;
      
    case UART_KEY5:
      gpio_turn(PTA14);
      // g_fDirectionKP += 1;
      break;
      
    case UART_KEY6: 
      gpio_turn(PTA14);
      // g_fDirectionKP -= 1;
      break;
      
    case UART_KEY7: 
      gpio_turn(PTA14);
      // g_fSteerKD += 1;
      break;
      
    case UART_KEY8: 
      gpio_turn(PTA14);
      // g_fSteerKD -= 1; 
      break;
      
    case UART_KEY9: 
      gpio_turn(PTA14);
      break;
      
    case UART_KEY10: 
      gpio_turn(PTA14);
      //steercentre += 1;
      break;
      
    case UART_KEY11: 
      gpio_turn(PTA14);
      // steercentre -= 1;
      break;
      
    case UART_KEY12:
      {
        static int i=0;
        gpio_turn(PTA14);
        i=1-i;
        // stop_car(i);
        break;
      }
    }
    frame_ready = FALSE;
  }
}

void Send_buleteeth(void)
{
  uart_send_param(0, BlueTeeth[0]>>8,BlueTeeth[0]&0x00ff);
  uart_send_param(1, BlueTeeth[1]>>8,BlueTeeth[1]&0x00ff);
  uart_send_param(2, BlueTeeth[2]>>8,BlueTeeth[2]&0x00ff);
  uart_send_param(3, BlueTeeth[3]>>8,BlueTeeth[3]&0x00ff);
  uart_send_param(4, BlueTeeth[4]>>8,BlueTeeth[4]&0x00ff);
  uart_send_param(5, BlueTeeth[5]>>8,BlueTeeth[5]&0x00ff);
}

void BluetoothParameters(void)
{
  BlueTeeth[0] = g_iSpeed;
  /*BlueTeeth[1] = g_iAverageSpeed;
  BlueTeeth[2] = g_u8Top1;
  BlueTeeth[3] = g_u8Top2;
  BlueTeeth[4] = g_u8Top3;
  BlueTeeth[5] = g_u8Top;*/
}

