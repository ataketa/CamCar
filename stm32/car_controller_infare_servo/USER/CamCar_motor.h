#include "stm32f10x.h"

void CamCar_Motor_Init();
void CamCar_Motor_CPIO_Config(void);
void CamCar_Motor_PWM_Init();

#define WHEEL_FORWARD 2
#define WHEEL_BACKWARD 1
#define WHEEL_STOP 0

#define CamCar_LEFTWHEEL_FORWARD() 	GPIO_SetBits(GPIOC,GPIO_Pin_6);GPIO_ResetBits(GPIOC,GPIO_Pin_7);
#define CamCar_LEFTWHEEL_BACKWARD() 	GPIO_ResetBits(GPIOC,GPIO_Pin_6);GPIO_SetBits(GPIOC,GPIO_Pin_7);															
#define CamCar_LEFTWHEEL_STOP() 			GPIO_ResetBits(GPIOC,GPIO_Pin_6);GPIO_ResetBits(GPIOC,GPIO_Pin_7);

#define CamCar_RIGHTWHEEL_FORWARD() 		GPIO_SetBits(GPIOC,GPIO_Pin_8);GPIO_ResetBits(GPIOC,GPIO_Pin_9);
#define CamCar_RIGHTWHEEL_BACKWARD() 	GPIO_ResetBits(GPIOC,GPIO_Pin_8);GPIO_SetBits(GPIOC,GPIO_Pin_9);															
#define CamCar_RIGHTWHEEL_STOP() 			GPIO_ResetBits(GPIOC,GPIO_Pin_8);GPIO_ResetBits(GPIOC,GPIO_Pin_9);

#define CamCar_stop()						CamCar_RIGHTWHEEL_STOP();CamCar_LEFTWHEEL_STOP();
#define CamCar_forward()				CamCar_RIGHTWHEEL_FORWARD();CamCar_LEFTWHEEL_FORWARD();
#define CamCar_backward()				CamCar_RIGHTWHEEL_BACKWARD();CamCar_LEFTWHEEL_BACKWARD();
#define CamCar_turnleft()				CamCar_RIGHTWHEEL_FORWARD();CamCar_LEFTWHEEL_BACKWARD();
#define CamCar_turnright()			CamCar_RIGHTWHEEL_BACKWARD();CamCar_LEFTWHEEL_FORWARD();
#define CamCar_forward_right()	CamCar_RIGHTWHEEL_STOP();CamCar_LEFTWHEEL_FORWARD();
#define CamCar_forward_left()		CamCar_RIGHTWHEEL_FORWARD();CamCar_LEFTWHEEL_STOP();
//#define CamCar_cam_up()			
//#define CamCar_cam_down()
