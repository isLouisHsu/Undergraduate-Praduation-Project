#include "pwm.h"

int16_t iSpeedSetLeft = 460;
int16_t iSpeedSetRight = 450;
int16_t iSpeedTurnOutside = 600;	//500+300
int16_t iSpeedTurnInside = 300;	//500-300
int16_t iSpeedLeft = 0;
int16_t iSpeedRight = 0;

void TIM2PwmInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	//使能时钟 - PA和TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//配置引脚
	//PA0~PA3 - TIM2_CH1~4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//配置定时器周期-500Hz(T=2ms)
	TIM_TimeBaseStructure.TIM_Period = 1000-1;	//一周期1000个计数脉冲，一个计数脉冲2us即0.5MHz
	TIM_TimeBaseStructure.TIM_Prescaler = 144;	//72MHz/0.5Mhz = 144分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	//配置定时器PWM输出
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM2,ENABLE);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2PwmOutput(int leftMotor, int rightMotor)
{
	if(leftMotor>=0)
	{
		TIM_SetCompare1(TIM2,leftMotor);
		TIM_SetCompare2(TIM2,0);
	}
	else
	{
		TIM_SetCompare1(TIM2,0);
		TIM_SetCompare2(TIM2,-leftMotor);
	}
	
	if(rightMotor>=0)
	{
		TIM_SetCompare3(TIM2,rightMotor);
		TIM_SetCompare4(TIM2,0);
	}
	else
	{
		TIM_SetCompare3(TIM2,0);
		TIM_SetCompare4(TIM2,-rightMotor);
	}
}
