#include "stm32f10x.h"
#include "usart1.h"
#include "i2c_self.h"
#include "CamCar_opcode.h"
#include "CamCar_motor.h"
#include "adc.h"
#include "pwm_output.h"

//#define ADC_THRESHOLD_VOLTAGE 1.0
//const float ADC_Threshold_Value = ADC_THRESHOLD_VOLTAGE/3.3*4096; //when ADC_THRESHOLD_VOLTAGE = 1.0v this value is approximately equal to 1241

const float ADC_Threshold_Value = 700;

extern __IO uint16_t ADC1_ConvertedValue; //adc 1 for front infare
extern __IO uint16_t ADC3_ConvertedValue; //adc 2 for back infare
extern u16 CCR_Val;


int front_ADC_value;
int back_ADC_value;


char recvword;
char opcode = CAMCAR_STOP;
char current_opcode_state = CAMCAR_STOP;


void delay(uint32_t a);
void updatestate_according_to_opcode(char opcode);
void test_motor();
int front_adc_clear();
int back_adc_clear();
void test_servo();

int main(void)
{
		
		
		//SystemInit();
		USART1_Config();
		I2C2_Slave_Init();
		CamCar_Motor_Init();
		//USART1_printf(USART1,"u_p hello\n");
		printf("hello\r\n");
		
		ADC1_Init();
		ADC3_Init();
		TIM4_PWM_Init();
		
	
		test_motor();
		test_servo();
		
	
		while(1){
			
			
			if(I2C_CheckEvent(I2C2,I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED)) printf("iic\r\n") ; 
			if(I2C_CheckEvent(I2C2,I2C_EVENT_SLAVE_BYTE_RECEIVED)){
					opcode = I2C_ReceiveData(I2C2);
					printf("recv:%c \r\n",opcode);
				
					if(front_adc_clear() == 0){
							if(opcode == CAMCAR_FORWARD || opcode == CAMCAR_FORWARD_LEFT || opcode == CAMCAR_FORWARD_RIGHT)
									opcode = CAMCAR_STOP;
					}
					if(back_adc_clear() == 0){
							if(opcode == CAMCAR_BACKWARD) 
									opcode = CAMCAR_STOP;
					}
					
			}
			else {
					printf("no command \r\n");
					opcode = CAMCAR_STOP;
			}
			
			
			/* avoiding vain update.if the current state is what the opcode requires,
			  there is no need for updating*/
			if(current_opcode_state != opcode){
					updatestate_according_to_opcode(opcode);
					printf("current state:%c \r\n",current_opcode_state);
					//delay(0x050000);
			}
			//printf("hello\r\n");
			delay(0x190000);
			
		}
		//return 0;
}

void delay(uint32_t a)
{
		while(a--);
}


void test_motor(){
		CamCar_forward();
		delay(0x800000);
		CamCar_backward();
		delay(0x800000);
		CamCar_stop();
		/*CamCar_turnright();
		delay(0x800000);
		CamCar_turnleft();
		delay(0x800000);
		CamCar_forward_left();
		delay(0x800000);
		CamCar_forward_right();*/
}

void	updatestate_according_to_opcode(char opcode)
{
		switch(opcode){
				case CAMCAR_FORWARD: CamCar_forward(); current_opcode_state = opcode; break;
				case CAMCAR_BACKWARD: CamCar_backward(); current_opcode_state = opcode; break;
				case CAMCAR_RIGHT: CamCar_turnright(); current_opcode_state = opcode; break;
				case CAMCAR_LEFT: CamCar_turnleft(); current_opcode_state = opcode; break;
				case CAMCAR_FORWARD_RIGHT: CamCar_forward_left(); current_opcode_state = opcode; break;
				case CAMCAR_FORWARD_LEFT: CamCar_forward_right(); current_opcode_state = opcode; break;
				case CAMCAR_STOP: CamCar_stop(); current_opcode_state = opcode; break;
				case CAMCAR_CAM_UP: CamCar_Cam_Up(); break;
				case CAMCAR_CAM_DOWN: CamCar_Cam_Down();break;
				default: CamCar_stop(); current_opcode_state = CAMCAR_STOP; break;
		}
}


int front_adc_clear()
{
		front_ADC_value = ADC1_ConvertedValue;
		printf("front adc:%d \r\n",front_ADC_value);
	  if(front_ADC_value > ADC_Threshold_Value) return 1; //clear! save to go
		else return 0; //there is obtstacle
}


int back_adc_clear()
{
		back_ADC_value = ADC3_ConvertedValue;
		printf("back adc:%d \r\n",back_ADC_value);
	  if(back_ADC_value > ADC_Threshold_Value) return 1; //clear! save to go
		else return 0; //there is obtstacle
}

void test_servo()
{
		int i=40;
		TIM_SetCompare3(TIM4,50);
		delay(0x1200000);
		TIM_SetCompare3(TIM4,60);
		delay(0x1200000);
		TIM_SetCompare3(TIM4,40);
		delay(0x1200000);
		TIM_SetCompare3(TIM4,50);
	
		
		/*while(i<60){
			//CamCar_Cam_Up();
			//delay(0x800000);
			printf("testing:%d\r\n",i);
			TIM_SetCompare3(TIM4, i);
			delay(0x800000);
			i++;
		}

		i=4;
		while(i--){
			CamCar_Cam_Down();
			delay(0x800000);
		}*/
}