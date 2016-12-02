#ifndef __PWM_OUTPUT_H
#define	__PWM_OUTPUT_H

#include "stm32f10x.h"


#define CamCar_Cam_Down()	if(CCR_Val < 60) CCR_Val ++; \
												else CCR_Val = 60;\
												TIM_SetCompare3(TIM4,CCR_Val);
#define CamCar_Cam_Up()	if(CCR_Val > 40) CCR_Val --; \
													else CCR_Val = 40;\
													TIM_SetCompare3(TIM4,CCR_Val);

void TIM4_PWM_Init(void);



#endif /* __PWM_OUTPUT_H */

