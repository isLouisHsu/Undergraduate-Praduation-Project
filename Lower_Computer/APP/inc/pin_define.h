
#ifndef PIN_DEFINE_
#define PIN_DEFINE_

// 蓝牙
// 线序 5V GND TXD RXD
#define BT_UART			UART4
#define BULETOOTH_RX	PTC14
#define BULETOOTH_TX 	PTC15

// 串口
// 线序 5V GND TXD RXD
#define DEBUG_UART		UART2
#define UART_RX			PTD2
#define UART_TX			PTD3

// 电机
// 线序 ?
#define MOTOR_CTRL		PTD8
#define MOTOR1			PTD4
#define MOTOR2			PTD5
#define MOTOR3			PTD6
#define MOTOR4			PTD7

// 舵机
// 线序: PWM  5V GND
#define STEER1			PTB18	
#define STEER2			PTB19

// CCD
// 线序:  SI CLK AI 5V GND  * 3
#define CCD1_DATA		ADC0_SE8  // PTB0			
#define CCD2_DATA		ADC0_SE9  // PTB1
#define CCD3_DATA		ADC0_SE12 // PTB2

#define CCD_SI			PTA28
#define CCD_CLK			PTA29

// 电磁
// 线序:  5V  AI GND
#define ELEC1_DATA		ADC0_SE13 // PTB3
#define ELEC2_DATA		ADC1_SE10 // PTB4
#define ELEC3_DATA		ADC1_SE11 // PTB5
#define ELEC4_DATA		ADC1_SE12 // PTB6
#define ELEC5_DATA		ADC1_SE13 // PTB7
#define ELEC6_DATA		ADC1_SE14 // PTB10


// 编码器1
// 编码器 :  VCC A  GND B 
#define COUNTER1_FTM	FTM1
#define COUNTER1_A		PTA13
#define COUNTER1_B		PTA12

// 编码器2
// 编码器 :  VCC A  GND B
#define COUNTER2_FTM	FTM2
#define COUNTER2_A		PTA10
#define COUNTER2_B		PTA11

// 摄像头1
// 线序:  Y1 Y3 Y5 Y7 NC RODD PCLK NC 5V
//		  Y0 Y2 Y4 Y6 NC HREF VSYN NC GND
#define CAM1_Y0			PTE0
#define CAM1_Y1			PTE1
#define CAM1_Y2			PTE2
#define CAM1_Y3			PTE3 
#define CAM1_Y4			PTE4
#define CAM1_Y5			PTE5 
#define CAM1_Y6			PTE6
#define CAM1_Y7			PTE7 
#define CAM1_FODD		PTD15
#define CAM1_PCLK		PTD12		// 像素同步
#define CAM1_HREF		PTD13	// 行同步
#define CAM1_VSYNC		PTD14		// 场同步

// 摄像头2
// 线序:  Y1 Y3 Y5 Y7 NC RODD PCLK NC 5V
//		  Y0 Y2 Y4 Y6 NC HREF VSYN NC GND
#define CAM2_Y0			PTB0
#define CAM2_Y1			PTB1
#define CAM2_Y2			PTB2
#define CAM2_Y3			PTB3 
#define CAM2_Y4			PTB4
#define CAM2_Y5			PTB5 
#define CAM2_Y6			PTB6
#define CAM2_Y7			PTB7 
#define CAM2_FODD		PTA28
#define CAM2_PCLK		PTA25		// 像素同步
#define CAM2_HREF		PTA26		// 行同步
#define CAM2_VSYNC		PTA27		// 场同步

// 拔码开关
#define SWITHC_DATA1	PTE26
#define SWITHC_DATA2	PTE27
#define SWITHC_DATA3	PTE28
#define SWITHC_DATA4	PTE12

// 按键
#define KEY1			PTE8			
#define KEY2			PTE9

// LED指示灯
#define LED1			PTE10
#define LED2			PTE11

// 液晶屏
// 线序 RST CE DC DIN CLK 5V BL GND
//#define LCD_RST			PTA7
//#define LCD_CE			PTA6
//#define LCD_DC			PTA8
//#define LCD_DIN			PTA9
//#define LCD_CLK			PTA16
//#define LCD_BL			PTA17

// 陀螺仪加速计
/*
#define ACC_X		    PTE24	
#define ACC_Z			PTE25
#define GYRO_X			PTC0
#define GYRO_Y			PTC1
*/
#endif
