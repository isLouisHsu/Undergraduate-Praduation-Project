#include "motor.h"

/*
**motor init 
*/
void MotorInit(uint32 freq)
{
	FTM_PWM_init(MOTOR_FTM, MOTOR_FTM_PASS_1,freq,0);		//FTM0_CH4:PTD4
	FTM_PWM_init(MOTOR_FTM, MOTOR_FTM_PASS_2,freq,0);		//FTM0_CH5:PTD5
	FTM_PWM_init(MOTOR_FTM, MOTOR_FTM_PASS_3,freq,0);		//FTM0_CH6:PTD6
	FTM_PWM_init(MOTOR_FTM, MOTOR_FTM_PASS_4,freq,0);		//FTM0_CH7:PTD7
}

/*
**C car motor drive
*/
void CMotorDrive(int speed1,int speed2)	//parameter range:"-1000~1000"
{
	uint32 duty1,duty2,duty3,duty4;
        
	if(speed1 >= 0) //forward
	{
          duty1=(uint32)speed1;
	  motor3(duty1);motor4(0);
	}
	else 	        //back
	{
	  duty2=(uint32)(ABS(speed1));
	  motor3(0);motor4(duty2);
	}
        
        if(speed2> 0)   //forward
        {
          duty3=(uint32)speed2;
	  motor1(duty3);motor2(0);
        }
        else            //back
        {
          duty4=(uint32)(ABS(speed2));
          motor1(0);motor2(duty4);
        }
}

/*
**B car motor drive
*/
void BMotorDrive(int speed)		//parameter range:"1~1000"
{
	uint32 duty;
	//forward
	if(speed >= 0)
	{
		duty=(uint32)speed;

		motor1(duty);
		motor2(0);
	}
	else 	//back
	{
		speed=ABS(speed);
		duty=(uint32)speed;

		//right
		motor1(0);
		motor2(speed);
	}
}

/*
**motor 1
*/
void motor1(uint32 duty)	//parameter range:"1~1000"
{
	uint32 cv;
    uint32 mod = 0;

    /*
    **duty cycle accuracy:1000u
    */
	ASSERT(duty <= 1000u);     //Assertion To detect the duty ratio is reasonable
	
	if(duty >= 999)			   //motor protect:limit duty
		duty=999;
	
    do
    {
        mod = FTM_MOD_REG(FTMN[MOTOR_FTM]);       //read MOD 
    }
    while(mod == 0);    

    cv = (duty * (mod - 0 + 1)) / 1000u;  
    FTM_CnV_REG(FTMN[MOTOR_FTM],MOTOR_FTM_PASS_1) = cv;
}

/*
**motor 2
*/
void motor2(uint32 duty)		//parameter range:"1~1000"
{
	uint32 cv;
    uint32 mod = 0;

    /*
    **duty cycle accuracy:1000u
    */
	ASSERT(duty <= 1000u);     //Assertion To detect the duty ratio is reasonable
	
	if(duty >= 999)			   //motor protect:limit duty
		duty=999;
	
    do
    {
        mod = FTM_MOD_REG(FTMN[MOTOR_FTM]);       //read MOD 
    }
    while(mod == 0);    

    cv = (duty * (mod - 0 + 1)) / 1000u;  
    FTM_CnV_REG(FTMN[MOTOR_FTM],MOTOR_FTM_PASS_2) = cv;
}

/*
**motor 3
*/
void motor3(uint32 duty)	//parameter range:"1~1000"
{
	uint32 cv;
    uint32 mod = 0;

    /*
    **duty cycle accuracy:1000u
    */
	ASSERT(duty <= 1000u);     //Assertion To detect the duty ratio is reasonable
	
	if(duty > 999)			   //motor protect:limit duty
		duty=999;
	
    do
    {
        mod = FTM_MOD_REG(FTMN[MOTOR_FTM]);       //read MOD 
    }
    while(mod == 0);    

    cv = (duty * (mod - 0 + 1)) / 1000u;  
    FTM_CnV_REG(FTMN[MOTOR_FTM],MOTOR_FTM_PASS_3) = cv;
}

/*
**motor 4
*/
void motor4(uint32 duty)	//parameter range:"1~1000"
{
	uint32 cv;
    uint32 mod = 0;

    /*
    **duty cycle accuracy:1000u
    */
	ASSERT(duty <= 1000u);     //Assertion To detect the duty ratio is reasonable
	
	if(duty > 999)			   //motor protect:limit duty
		duty=999;
	
    do
    {
        mod = FTM_MOD_REG(FTMN[MOTOR_FTM]);       //read MOD 
    }
    while(mod == 0);    

    cv = (duty * (mod - 0 + 1)) / 1000u;  
    FTM_CnV_REG(FTMN[MOTOR_FTM],MOTOR_FTM_PASS_4) = cv;
}
