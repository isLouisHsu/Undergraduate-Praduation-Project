#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "led.h"
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
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
//����봮���жϽ��գ��벻Ҫע�����º궨��
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define USART1_Test				1		//���ڲ��Ժ궨��
#define USART2_Test				1		//���ڲ��Ժ궨��


extern u8 rxData[10];
extern u8 rxStatus;
extern u8 isReceived;
extern u8  rxAngleDir;
extern u8  rxAngle;  
extern int16_t rxIntAngle;
extern int16_t rxIntAngleLast;
extern u8  rxIsInsight;
extern u16 rxDistance;

extern u8  USART1_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART2_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         	   	//����״̬���
extern u16 USART2_RX_STA;         		//����״̬���

extern void uart1_init(u32 bound);
extern void uart2_init(u32 bound);
extern void usart_test (void);
extern void usart_sendchar(USART_TypeDef* USARTx,char c);
extern void usart_sendstr (USART_TypeDef* USARTx, char *str);
extern void usart_putbuff (USART_TypeDef* USARTx, char *buff, uint16_t len);
#endif


