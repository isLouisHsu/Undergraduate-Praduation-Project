/***********************************************************************************************
/                             oledÄ£¿éº¯Êý----hÎÄ¼þ
/-----------------------------------------------------------------------------------------------
/----ÌÔ±¦£º³ÛÈð×Ýºáµç×Ó¿Æ¼¼			http://crzongheng.taobao.com
/----°æ±¾£ºV1.0		
/----Ê±¼ä£º2013-10-18
/----ËµÃ÷£º
***********************************************************************************************/

#ifndef __OLED_H__
#define __OLED_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "include.h"


//***************************************ºê¶¨Òå±äÁ¿*********************************************
//IO¿Ú²Ù×÷ºê¶¨Òå
/*
	SCL  -->  PTA 
	SDA  -->  PTD1
	RST  -->  PTD2
	D/C  -->  PTD3
*/
/*Ê¹ÓÃshouhcuangk60Ê±ÓÃµÄOLED¹Ü½Å*/
#if 0
  #define LED_SCL 	PTA14
  #define LED_SDA		PTA15
  #define LED_RST		PTA17
  #define LED_DC		PTA8
  #define LED_CS          PTA9
#endif
/*Ê¹ÓÃLQK60Ê±ÓÃµÄOLED¹Ü½Å*/
#if 1
   #define LED_SCL 	PTC16
   #define LED_SDA	PTC17
   #define LED_RST	PTC18
   #define LED_DC	  PTC19
   #define LED_CS   PTA9    //  Õâ¸ö¹Ü½ÅÆäÊµÃ»ÓÃµ½
#endif
   
   

#define OLED_CS_H   gpio_set(LED_CS, 1)
#define OLED_SCL_H	gpio_set(LED_SCL, 1)
#define OLED_SCL_L	gpio_set(LED_SCL, 0)
 
#define OLED_SDA_H	gpio_set(LED_SDA, 1)
#define OLED_SDA_L	gpio_set(LED_SDA, 0)

#define OLED_RST_H	gpio_set(LED_RST, 1)
#define OLED_RST_L	gpio_set(LED_RST, 0)

#define OLED_DC_H	gpio_set(LED_DC, 1)
#define OLED_DC_L	gpio_set(LED_DC, 0)
 
//ÏÔÊ¾µÄÊôÐÔ
#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xCF
#define X_WIDTH 	128
#define Y_WIDTH 	64

//***************************************º¯ÊýÉùÃ÷***********************************************
void OLED_WrDat(unsigned char dat);//Ð´Êý¾Ý
void OLED_WrCmd(unsigned char cmd);//Ð´ÃüÁî
void OLED_Point_init(void);//Ê¹ÓÃ¶Ë¿Ú³õÊ¼»¯

void OLED_Init(void);//³õÊ¼»¯
void OLED_CLS(void);//ÇåÆÁ
void OLED_Fill(unsigned char bmp_dat);//È«ÆÁÌî³ä
void OLED_SetPos(unsigned char x, unsigned char y);//ÉèÖÃÆðÊ¼µã×ø±ê

void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);//ÏÔÊ¾6*8µÄµãÕó×Ö·û´®
void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);//ÏÔÊ¾8*16µÄµãÕó×Ö·û´®
void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char ch[]);//ÏÔÊ¾16*16µÄºº×Ö×Ö·û´®
void OLED_Print(unsigned char x, unsigned char y, unsigned char ch[]);//ÏÔÊ¾ºº×ÖºÍÓ¢ÎÄ»ìºÏµÄ×Ö·û´®
void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);//ÏÔÊ¾Í¼Æ¬
void OLED_Dis_Num(unsigned char x,unsigned char y,unsigned int num,unsigned char N);//ÏÔÊ¾±äÁ¿
void OLED_Dis_Float(unsigned char x,unsigned char y,double FL,unsigned char N);//ÏÔÊ¾Ë«¾«¶ÈµÄ±äÁ¿
void OLED_Dis_Float_LARGE(unsigned char x,unsigned char y,double FL,unsigned char N);//ÏÔÊ¾Ë«¾«¶ÈµÄ±äÁ¿

/****************************/
extern unsigned char oled_picture[1024];
void OledShowCamera1(uint8 *camera_arry,uint8 width,uint8 height);
void OLED_DrawPoint(uint8 x,uint8 y,uint8 t);
void OLED_Fill_1(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 dot);
void OLED_Refresh_Gram(void);
void ShowBecanCenterLine(uint8 x,uint8 y,uint8 dot);
void ShowBecanCenterPoint(uint8 x,uint8 y,uint8 dot);
void Oled_display_large_1(float m1,float m2,float m3,float m4);

/***************************/

#ifdef __cplusplus
}
#endif

#endif
 //****************************************END***************************************************

void Oled_display_large(float m1,float m2,float m3,float m4);