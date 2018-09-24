#include "steering.h"

/*
**steering init
*/

void SteeringInit(void)				
{
	FTM_PWM_init(STEERING_FTM, STEERING_FTM_PASS,100,1);			//FTM2_CH1 :PTB19
	SteeringPwm(g_iSteeringMid);
}

/*
**steering control
*/
void SteeringPwm(uint32 steering_parameter )
{
	uint32 cv;
    uint32 mod = 0;
	uint32 duty;
	
	/*
	**steering protect :0~180 degree; 1000u:40~260 each steering gear may be slightly different.
    */
    if(steering_parameter >=157)  //153
		steering_parameter = 157;
	if(steering_parameter<=126)//126
		steering_parameter = 126;
        duty=steering_parameter;

	/*if(steering_parameter >=79)  
		steering_parameter =79 ;
	if(steering_parameter<=62)
		steering_parameter = 62;
        
	duty=steering_parameter;
*/
	/*
    **duty cycle accuracy:1000u
    */
	ASSERT(duty <= 1000u);     //Assertion To detect the duty ratio is reasonable
	
    do
    {
        mod = FTM_MOD_REG(FTMN[STEERING_FTM]);        //read  MOD  
    }
    while(mod == 0);    

    cv = (duty * (mod - 0 + 1)) / 1000u;  
    FTM_CnV_REG(FTMN[STEERING_FTM], STEERING_FTM_PASS) = cv;		
}