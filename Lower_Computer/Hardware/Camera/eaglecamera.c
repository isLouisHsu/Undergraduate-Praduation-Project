#include "eaglecamera.h"

uint8 imgbuff[OV7725_EAGLE_SIZE];       //Primitive Image Buff
uint8 u8_EagleImgBuffer[OV7725_EAGLE_H][OV7725_EAGLE_W];   // 60x160  Storage camera data

/*
**eagle camera init
*/
void EagleCameraInit()
{
	camera_init(imgbuff);

	enable_irq(PORTA_IRQn);

	set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);   

	set_irq_priority(DMA0_IRQn,0);                      
    set_irq_priority(PORTA_IRQn, 2);                        
}

/*
POART A irq
*/
void PORTA_IRQHandler()
{
    uint8  n;    //pin number
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                              //Clear interrupt flag

    n = 29;                                        //Field interruption               

    if(flag & (1 << n))                            //PTA29 Field interruption
    {   
    
      if(g_iJudege == 0)
      {
       /*
       **ï¼?       */
/*
PORTA_ISFR = 1 <<  PT10;              //clear PLCK
DMA_EN(CAMERA_DMA_CH);                //EN DMA
PORTA_ISFR = 1 <<  PT10;              //clear PLCK
DMA_DADDR(CAMERA_DMA_CH) = (uint32)img_buff;    //Reply address
ov7725_eagle_img_flag=IMG_START;
*/
        ov7725_eagle_vsync(); 
      }
        
        if(g_iJudege == 1)
        {
            if(ov7725_eagle_img_flag==IMG_FINISH)   
             GetImg((void *)u8_EagleImgBuffer);         //Obtain image 
             g_iMain = 1;
        }  
     }

    g_iJudege++;

/*
**an image, a control
*/
    if(g_iJudege >= 2 )
        g_iJudege = 0;
}

void DMA0_IRQHandler()
{
    camera_dma();
}

void GetImg(void *img)
{
	img_extract(img,imgbuff,OV7725_EAGLE_W*OV7725_EAGLE_H/8);
}

