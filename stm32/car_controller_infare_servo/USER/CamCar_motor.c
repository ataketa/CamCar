#include "CamCar_motor.h"

void CamCar_Motor_Init()
{
		CamCar_Motor_CPIO_Config();
		CamCar_Motor_PWM_Init();
}

void CamCar_Motor_CPIO_Config(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOC������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/* initialize PC6 PC7 PC8 PC9 */
		/*ѡ��Ҫ���Ƶ�GPIOC����*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 ;	
	/*���ÿ⺯������ʼ��GPIOC*/
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
		
	/* initialize PB0 PB1 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		
}


void CamCar_Motor_PWM_Init()
{
		/* to be develop later */
		/* now we use always high voltage */
		GPIO_SetBits(GPIOB,GPIO_Pin_0);GPIO_SetBits(GPIOB,GPIO_Pin_1);
	 
}