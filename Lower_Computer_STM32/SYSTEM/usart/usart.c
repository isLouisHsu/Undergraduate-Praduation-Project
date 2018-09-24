#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
 
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART1_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART2_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
//����״̬
u16 USART1_RX_STA=0;    //�Զ���Ĵ���
						//bit15��	������ɱ�־
						//bit14��	���յ�0x0d
						//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;	//�Զ���Ĵ���
						//bit15�� ������ɱ�־
						//bit14��
						//bit13, 
						//bit12,  
						//bit11~0��   ���յ�����Ч�ֽ���Ŀ

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
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);//�ȴ����ͽ���
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

//���Բ���
void usart_test (void)
{
	u8 t;
	u8 len; 
	#if	USART1_Test
	if(USART1_RX_STA&0x8000)
	{					   
		len=USART1_RX_STA&0x3fff;
		printf("\r\n�����͵�����Ϊ:\r\n");
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
		printf("\r\n�����͵�����Ϊ:\r\n");
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
    //GPIO�˿�����
 	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
	   
	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void uart2_init(u32 bound){
  //GPIO�˿�����
 	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);	//ʹ��GPIOAʱ��
	//USART2_TX   GPIOA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.2
	   
	//USART2_RX	  GPIOA.3��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3 

	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); //��ʼ������1
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���1 

}

#if EN_USART1_RX
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 res;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
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


#if EN_USART2_RX   //���ʹ���˽���
void USART2_IRQHandler(void)                	//����2�жϷ������
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		
		#if 1
		if(Res!=0x0a&&Res!=0x0d)
			{
			USART2_RX_BUF[USART2_RX_STA&0XFFF]=Res ;
			USART2_RX_STA++;		//USART2_RX_STA&0XFFF��������д��ͬʱ���ԭ���ݣ����ҷ�ֹ��һ�����ݸ���
			if(USART2_RX_STA>(USART_REC_LEN-1)) USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	
			}
		#endif
		
		#if 0
		if((USART2_RX_STA&0x8000)==0)//����δ���
			{
			if((USART2_RX_STA&0x2000)==0)	 //��δ��������"\r\n"
				{
				if((USART2_RX_STA&0x1000)==0)//��δ����һ��"\r\n"
					{
					if(USART2_RX_STA&0x4000)//���յ���0x0d
						{
						if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
						else USART2_RX_STA&=0x1000;	//���������һ��"\r\n"
						LCD_ShowString(20,44,300,12,12,"\r\n once");
						}
					else //��û�յ�0X0D
						{	
						if(Res==0x0d)USART2_RX_STA|=0x4000; 
						}
					}
				else						//���յ�һ��"\r\n"
					{
					if(USART2_RX_STA&0x4000)//���յ���0x0d
						{
						if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
						else USART2_RX_STA&=0x2000;	//�������������"\r\n"
						LCD_ShowString(20,56,300,12,12,"\r\n twice");
						}
					else //��û�յ�0X0D
						{	
						if(Res==0x0d)USART2_RX_STA|=0x4000; 
						}
					}
				}
			else							//���յ�����"\r\n"
				{
				if(USART2_RX_STA&0x4000)//���յ���0x0d
					{
					if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
					else USART2_RX_STA|=0x8000;	//��������� 
					LCD_ShowString(20,68,300,12,12,"usart2 receive done");
					}
				else //��û�յ�0X0D
					{	
					if(Res==0x0d)USART2_RX_STA|=0x4000;
					else
						{
						USART2_RX_BUF[USART2_RX_STA&0XFFF]=Res ;
						USART2_RX_STA++;		//USART2_RX_STA&0XFFF��������д��ͬʱ���ԭ���ݣ����ҷ�ֹ��һ�����ݸ���
						if(USART2_RX_STA>(USART_REC_LEN-1)) USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
						}		 
					}
				}
			}
		#endif
		}
	
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
}
#endif	

