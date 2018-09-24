#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
 
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART1_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u8 USART2_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
//接收状态
u16 USART1_RX_STA=0;    //自定义寄存器
						//bit15，	接收完成标志
						//bit14，	接收到0x0d
						//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;	//自定义寄存器
						//bit15， 接收完成标志
						//bit14，
						//bit13, 
						//bit12,  
						//bit11~0，   接收到的有效字节数目

u8  rxData[10] = {0};
u8  rxStatus = 0;
u8  isReceived = 0;
u8  rxAngleDir = 0;
u8  rxAngle = 0;  
int16_t rxIntAngle = 0;
int16_t rxIntAngleLast = 0;
u8  rxIsInsight = 0;
u16 rxDistance = 0;

void usart_sendchar(USART_TypeDef* USARTx,char c)
{
	USART_SendData(USARTx,(uint16_t)c);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);//等待发送结束
}
void usart_sendstr (USART_TypeDef* USARTx, char *str)
	{
	while(*str!='\0')
		{
		usart_sendchar(USARTx,*str);
		str++;
		}
	}
void usart_putbuff (USART_TypeDef* USARTx, char *buff, uint16_t len)
	{
	while(len--)
		{
		usart_sendchar(USARTx,*buff);
		buff++;
		}
	}

//回显测试
void usart_test (void)
{
	u8 t;
	u8 len; 
	#if	USART1_Test
	if(USART1_RX_STA&0x8000)
	{					   
		len=USART1_RX_STA&0x3fff;
		printf("\r\n您发送的数据为:\r\n");
		for(t=0;t<len;t++)
		{
			USART1->DR=USART1_RX_BUF[t];
			while((USART1->SR&0X40)==0);
			}
		printf("\r\n\r\n");
		USART1_RX_STA=0;
	}
	#elif USART2_Test
	if(USART2_RX_STA&0x8000)
	{	
		len=USART2_RX_STA&0x3fff;
		printf("\r\n您发送的数据为:\r\n");
		for(t=0;t<len;t++)
		{
			USART2->DR=USART2_RX_BUF[t];
			while((USART2->SR&0X40)==0);
		}
		printf("\r\n\r\n");
		USART2_RX_STA=0;
	}
	#endif
}

void uart1_init(u32 bound){
    //GPIO端口设置
 	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
	   
	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void uart2_init(u32 bound){
  //GPIO端口设置
 	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);	//使能GPIOA时钟
	//USART2_TX   GPIOA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
	   
	//USART2_RX	  GPIOA.3初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3 

	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART2, &USART_InitStructure); //初始化串口1
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART2, ENABLE);                    //使能串口1 

}

#if EN_USART1_RX
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 res;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		res =USART_ReceiveData(USART1);	//读取接收到的数据
		
		if			(rxStatus==0 && res==0x5a)rxStatus = 1;				//0x5a
		else if	(rxStatus==1){rxData[0] = res;rxStatus = 2;}	//dirAngle
		else if	(rxStatus==2){rxData[1] = res;rxStatus = 3;}	//angle
		else if	(rxStatus==3){rxData[2] = res;rxStatus = 4;}	//IsInView
		else if	(rxStatus==4){rxData[3] = res;rxStatus = 5;}
		else if	(rxStatus==5){rxData[4] = res;rxStatus = 6;}	//distance & 0x00ff
		else if	(rxStatus==6){rxData[5] = res;rxStatus = 7;}	//distance / 256
		else if	(rxStatus==7 && res==0x61){isReceived=1;rxStatus=0;LED1=!LED1;}
		else rxStatus = 0;
  }
}
#endif


#if EN_USART2_RX   //如果使能了接收
void USART2_IRQHandler(void)                	//串口2中断服务程序
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		
		#if 1
		if(Res!=0x0a&&Res!=0x0d)
			{
			USART2_RX_BUF[USART2_RX_STA&0XFFF]=Res ;
			USART2_RX_STA++;		//USART2_RX_STA&0XFFF计数可在写入同时清除原数据，并且防止上一次数据干扰
			if(USART2_RX_STA>(USART_REC_LEN-1)) USART2_RX_STA=0;//接收数据错误,重新开始接收	
			}
		#endif
		
		#if 0
		if((USART2_RX_STA&0x8000)==0)//接收未完成
			{
			if((USART2_RX_STA&0x2000)==0)	 //还未接收两次"\r\n"
				{
				if((USART2_RX_STA&0x1000)==0)//还未接收一次"\r\n"
					{
					if(USART2_RX_STA&0x4000)//接收到了0x0d
						{
						if(Res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
						else USART2_RX_STA&=0x1000;	//接收完成了一次"\r\n"
						LCD_ShowString(20,44,300,12,12,"\r\n once");
						}
					else //还没收到0X0D
						{	
						if(Res==0x0d)USART2_RX_STA|=0x4000; 
						}
					}
				else						//接收到一次"\r\n"
					{
					if(USART2_RX_STA&0x4000)//接收到了0x0d
						{
						if(Res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
						else USART2_RX_STA&=0x2000;	//接收完成了两次"\r\n"
						LCD_ShowString(20,56,300,12,12,"\r\n twice");
						}
					else //还没收到0X0D
						{	
						if(Res==0x0d)USART2_RX_STA|=0x4000; 
						}
					}
				}
			else							//接收到两次"\r\n"
				{
				if(USART2_RX_STA&0x4000)//接收到了0x0d
					{
					if(Res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
					else USART2_RX_STA|=0x8000;	//接收完成了 
					LCD_ShowString(20,68,300,12,12,"usart2 receive done");
					}
				else //还没收到0X0D
					{	
					if(Res==0x0d)USART2_RX_STA|=0x4000;
					else
						{
						USART2_RX_BUF[USART2_RX_STA&0XFFF]=Res ;
						USART2_RX_STA++;		//USART2_RX_STA&0XFFF计数可在写入同时清除原数据，并且防止上一次数据干扰
						if(USART2_RX_STA>(USART_REC_LEN-1)) USART2_RX_STA=0;//接收数据错误,重新开始接收	  
						}		 
					}
				}
			}
		#endif
		}
	
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
}
#endif	

