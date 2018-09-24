#include "Imageprocessing.h"

int g_iJudege = 0;      //g_iJudege=1:Collecting image ;g_iJudege=0,control
int g_iThreshold = 30;
int g_iMain = 0; 
uint8 g_u8Top = 0;
uint8 g_u8LastTop = 0;
uint8 g_u8BeaconLocation = 0;
uint8 g_u8LastBeaconLocation = 0;
uint8 g_u8FindBeacon = 0;
float g_fDeviation = 0,g_fLastDeviation = 0,g_fTwoDeviation= 0;
float g_faddimage=0;

/**********Specific parameter:EagalCameraBeaconHandle2**********/
uint8 g_u8FFPoint = 0 ;             //FindFirstPoint
uint8 g_u8FSPoint = 0 ;             //FindSecondPoint
uint8 g_u8LRelCoe = 1 ;             //LINE Reliability coefficient
uint8 g_u8CRelCoe = 1 ;             //COLUMN Reliability coefficient8
uint8 g_u8OledShowLX= 0 ;
uint8 g_u8OledShowLY= 0 ;
uint8 g_u8OledShowRX= 0 ;
uint8 g_u8OledShowRY= 0 ;
uint8 g_OledShowPermit = 0 ;
/******************/


/*
** picture binaryzation
*/
void CameraBinaryzation(void)
{
	 u8 *p_Image,*q_Image;

	 q_Image=&u8_FinishProcessingBuffer[0][0];
	 for(p_Image=&u8_PendingTreatmentBuffer[0][0];p_Image<=&u8_PendingTreatmentBuffer[LINE-1][COLUMN-1];p_Image++)  //将采回的数据缓存给p_Image数组
 	 {
    	if((*p_Image>g_iThreshold)&&(*(p_Image+1)>g_iThreshold)||(*p_Image>g_iThreshold)&&(*(p_Image-1)>g_iThreshold))   //此处进行了一次滤�?  
      	 *q_Image++ = WHITE1;    // black:0  white:255  
   	 	else
      	 *q_Image++ = BLACK1;
 	 }
}
void PredatorCameraBeaconHandle1(void)
{
    g_u8FindBeacon = 0;
    g_u8Top = 0; 
    //g_u8Top = 0;
    //g_u8Find = 0;
    //u8 u8_LeftColumn = 0,u8_RightColumn = COLUMN;
    uint8 i=0,j=0,u8_LeftBeaconLocation=0,u8_RightBeaconLocation= COLUMN-1;
    
    for(i=0;i<LINE;i++)
    {
        for(j=0;j<COLUMN;j++)
        {
            if((u8_FinishProcessingBuffer[i][j] ==BLACK) && (u8_FinishProcessingBuffer[i][j+1] ==WHITE) &&(u8_LeftBeaconLocation == 0))
            {
                u8_LeftBeaconLocation= j;       //determination of the left edge of the beacon lamp
            }
            else 
              if((u8_FinishProcessingBuffer[i][j] == WHITE) && (u8_FinishProcessingBuffer[i][j+1] == BLACK) && (u8_RightBeaconLocation == COLUMN-1))
              {
                u8_RightBeaconLocation= j;  //determination of the right edge of the beacon lamp
              }     
        }

        if((u8_LeftBeaconLocation!=0)||(u8_RightBeaconLocation!=COLUMN-1)) 
        {
            g_u8Top = i;
            g_u8FindBeacon = 1;
            break;
        }
    }

/*
**Calculation of the specific position of the beacon light
*/
    if((u8_LeftBeaconLocation!=0) ||(u8_RightBeaconLocation!=COLUMN-1))
    {
        g_u8BeaconLocation = (u8_LeftBeaconLocation+u8_RightBeaconLocation)/2;
    }
    else
     g_u8BeaconLocation = g_u8LastBeaconLocation;

    /*
    **Deviation calculation
    */
    g_fDeviation = g_u8BeaconLocation -(COLUMN/2); 
    g_fTwoDeviation = g_fDeviation - g_fLastDeviation ;//differential
}

void PredatorCameraBeaconHandle2(void)
{
   uint8 i=0,j=0,u8_LeftBeaconLocationX=0,u8_RightBeaconLocationX= COLUMN-1,u8_LeftBeaconLocationY=0,u8_RightBeaconLocationY=LINE-1;
  
   for(i=1;i<LINE-1;i++)
    {
        for(j=1;j<COLUMN-1;j++)
        {
            if((u8_FinishProcessingBuffer[i][j-g_u8CRelCoe] ==WHITE) && (u8_FinishProcessingBuffer[i][j] ==WHITE) && (u8_FinishProcessingBuffer[i][j+g_u8CRelCoe] ==WHITE)&& (u8_FinishProcessingBuffer[i-g_u8LRelCoe][j] ==WHITE)&& (u8_FinishProcessingBuffer[i+g_u8LRelCoe][j] ==WHITE)&&(u8_LeftBeaconLocationX == 0)&&(u8_LeftBeaconLocationY == 0))
            {
                u8_LeftBeaconLocationX = j ;        //determination of the left edge of the beacon lamp
                u8_LeftBeaconLocationY = i ;

                g_u8OledShowLX = u8_LeftBeaconLocationX;
                g_u8OledShowLY = u8_LeftBeaconLocationY;

                g_u8FFPoint = 1 ;
                break;                       //Out of column cycle                
            }
        }
        if(g_u8FFPoint == 1)
          break;                              //Out of the line cycle
    }
    if(g_u8FFPoint == 1)              // Only to find the first point, only to find second points
    {
        for(i=LINE-2;i>0;i--)
        {
          for(j=COLUMN-2;j>0;j--)
          {
            if((u8_FinishProcessingBuffer[i][j-g_u8CRelCoe] ==WHITE) && (u8_FinishProcessingBuffer[i][j] ==WHITE) && (u8_FinishProcessingBuffer[i][j+g_u8CRelCoe] ==WHITE) && (u8_FinishProcessingBuffer[i+g_u8LRelCoe][j] ==WHITE) && (u8_FinishProcessingBuffer[i-g_u8LRelCoe][j]==WHITE)&&(u8_RightBeaconLocationX == (COLUMN-1))&&(u8_RightBeaconLocationY == (LINE-1)))
            {
                u8_RightBeaconLocationX = j ;        //determination of the left edge of the beacon lamp
                u8_RightBeaconLocationY = i ;

                g_u8OledShowRX = u8_RightBeaconLocationX;
                g_u8OledShowRY = u8_RightBeaconLocationY;

                g_u8FSPoint = 1 ;
                break;                              //Out of column cycle
            }
          } 
          if(g_u8FSPoint == 1 )         
             break;                                 //Out of the line cycle
        }
    }

/*
**Calculation of the specific position of the beacon light
*/
    if(g_u8FSPoint == 1 )      // When second points were discovered, it was determined that the beacon was found
    {
        g_u8Top = (u8_LeftBeaconLocationY+u8_RightBeaconLocationY)/2;                   //LINE of point
        g_u8BeaconLocation =(u8_LeftBeaconLocationX+u8_RightBeaconLocationX)/2;         //COLUMN of point
        g_u8FindBeacon = 1;
    }
    else
    {
        g_u8FindBeacon = 0;
        g_u8Top = 0;
    }
   
  
    /*
    **Deviation calculation
    */
   //g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+3; 
   	g_fDeviation = g_u8BeaconLocation -(COLUMN/2); 
   //g_fDeviation = g_u8BeaconLocation -(COLUMN/2)-3; 
    g_fTwoDeviation = g_fDeviation - g_fLastDeviation ;//differential
}


/*
**Beacon processing algorithm 1:Only to find the left and right two boundary points
*/
void EagalCameraBeaconHandle1(void)
{
    g_u8FindBeacon = 0;
    g_u8Top = 0; 
    //g_u8Top = 0;
    //g_u8Find = 0;
    //u8 u8_LeftColumn = 0,u8_RightColumn = COLUMN;
    uint8 i=0,j=0,u8_LeftBeaconLocation=0,u8_RightBeaconLocation= COLUMN-1;
    
    for(i=0;i<LINE;i++)
    {
        for(j=0;j<COLUMN;j++)
        {
            if((u8_EagleImgBuffer[i][j] ==BLACK) && (u8_EagleImgBuffer[i][j+1] ==WHITE) &&(u8_LeftBeaconLocation == 0))
            {
                u8_LeftBeaconLocation= j;       //determination of the left edge of the beacon lamp
            }
            else 
              if((u8_EagleImgBuffer[i][j] == WHITE) && (u8_EagleImgBuffer[i][j+1] == BLACK) && (u8_RightBeaconLocation == COLUMN-1))
              {
                u8_RightBeaconLocation= j;  //determination of the right edge of the beacon lamp
              }     
        }

        if((u8_LeftBeaconLocation!=0)||(u8_RightBeaconLocation!=COLUMN-1)) 
        {
            g_u8Top = i;
            g_u8FindBeacon = 1;
            break;
        }
    }

/*
**Calculation of the specific position of the beacon light
*/
    if((u8_LeftBeaconLocation!=0) ||(u8_RightBeaconLocation!=COLUMN-1))
    {
        g_u8BeaconLocation = (u8_LeftBeaconLocation+u8_RightBeaconLocation)/2;
    }
    else
     g_u8BeaconLocation = g_u8LastBeaconLocation;

    /*
    **Deviation calculation
    */
    g_fDeviation = g_u8BeaconLocation -(COLUMN/2); 
    g_fTwoDeviation = g_fDeviation - g_fLastDeviation ;//differential
}

/*
**Beacon processing algorithm 2: Find two points on the diagonal, and calculate the average point
*/
void EagalCameraBeaconHandle2(void)
{
   uint8 i=0,j=0,u8_LeftBeaconLocationX=0,u8_RightBeaconLocationX= COLUMN-1,u8_LeftBeaconLocationY=0,u8_RightBeaconLocationY=LINE-1;
  
   for(i=1;i<LINE-1;i++)
    {
        for(j=1;j<COLUMN-1;j++)
        {
            if((u8_EagleImgBuffer[i][j-g_u8CRelCoe] ==WHITE) && (u8_EagleImgBuffer[i][j] ==WHITE) && (u8_EagleImgBuffer[i][j+g_u8CRelCoe] ==WHITE)&& (u8_EagleImgBuffer[i-g_u8LRelCoe][j] ==WHITE)&& (u8_EagleImgBuffer[i+g_u8LRelCoe][j] ==WHITE)&&(u8_LeftBeaconLocationX == 0)&&(u8_LeftBeaconLocationY == 0))
            {
                u8_LeftBeaconLocationX = j ;        //determination of the left edge of the beacon lamp
                u8_LeftBeaconLocationY = i ;

                g_u8OledShowLX = u8_LeftBeaconLocationX;
                g_u8OledShowLY = u8_LeftBeaconLocationY;

                g_u8FFPoint = 1 ;
                break;                       //Out of column cycle                
            }
        }
        if(g_u8FFPoint == 1)
          break;                              //Out of the line cycle
    }
    if(g_u8FFPoint == 1)              // Only to find the first point, only to find second points
    {
        for(i=LINE-2;i>0;i--)
        {
          for(j=COLUMN-2;j>0;j--)
          {
            if((u8_EagleImgBuffer[i][j-g_u8CRelCoe] ==WHITE) && (u8_EagleImgBuffer[i][j] ==WHITE) && (u8_EagleImgBuffer[i][j+g_u8CRelCoe] ==WHITE) && (u8_EagleImgBuffer[i+g_u8LRelCoe][j] ==WHITE) && (u8_EagleImgBuffer[i-g_u8LRelCoe][j]==WHITE)&&(u8_RightBeaconLocationX == (COLUMN-1))&&(u8_RightBeaconLocationY == (LINE-1)))
            {
                u8_RightBeaconLocationX = j ;        //determination of the left edge of the beacon lamp
                u8_RightBeaconLocationY = i ;

                g_u8OledShowRX = u8_RightBeaconLocationX;
                g_u8OledShowRY = u8_RightBeaconLocationY;

                g_u8FSPoint = 1 ;
                break;                              //Out of column cycle
            }
          } 
          if(g_u8FSPoint == 1 )         
             break;                                 //Out of the line cycle
        }
    }

/*
**Calculation of the specific position of the beacon light
*/
    if(g_u8FSPoint == 1 )      // When second points were discovered, it was determined that the beacon was found
    {
      
        g_u8Top = (u8_LeftBeaconLocationY+u8_RightBeaconLocationY)/2;                   //LINE of point
        g_u8BeaconLocation =(u8_LeftBeaconLocationX+u8_RightBeaconLocationX)/2;         //COLUMN of point
        g_u8FindBeacon = 1;
        g_OledShowPermit = 1;           //Permit oled show center line/point
    }
    else
    {
        g_u8FindBeacon = 0;
        g_u8Top = 0;
        //g_u8BeaconLocation = 160;
        g_OledShowPermit = 0;
    }
   
  
    /*
    **Deviation calculation
    */

 //if(g_iAverageSpeed>300)
 //{
     // g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+33; 
 //}
 /*else
   if(g_iAverageSpeed>250)
     g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+33; 
    else
   if(g_iAverageSpeed>200)
     g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+29; 
     else
   if(g_iAverageSpeed>150)
     g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+23; 
      else
   if(g_iAverageSpeed>100)
     g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+17; 
      else
   if(g_iAverageSpeed>50)
     g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+11; */
  //else
  /*  if(g_u8Top < 13 && g_u8Top >0 )
    {
       g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+15; 
    }
   else
     if(g_u8Top < 17 && g_u8Top >=13 )
       g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+20; 
    else
      if(g_u8Top >= 17 )
        g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+25; */
  /* if(g_u8Top < 13 && g_u8Top >0 )
    {
       g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+12; 
    }
   else
     if(g_u8Top < 17 && g_u8Top >=13 )
       g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+14; 
    else
      if(g_u8Top >= 17 )
        g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+19;*/
  //  g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+7-8;   //Left
      g_fDeviation = g_u8BeaconLocation -(COLUMN/2)+7+8;   //Right
   
   
    g_fTwoDeviation = g_fDeviation - g_fLastDeviation ;//differential
}


