/********************************************************************************
 * �ļ���  ��i2c_ee.c
 * ����    ��i2c EEPROM(AT24C02)Ӧ�ú�����         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�-----------------
 *          |                 |
 *          |  PB6-I2C1_SCL	  |
 *          |  PB7-I2C1_SDA   |
 *          |                 |
 *           -----------------
 * ��汾  ��ST3.5.0
 * ����    ������ 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "i2c_self.h"

#define I2C_Speed              4000
//#define I2C1_OWN_ADDRESS7    0x0A
#define I2C2_OWN_ADDRESS7    0x25
#define I2C_PageSize           8			/* AT24C02ÿҳ��8���ֽ� */

uint16_t EEPROM_ADDRESS;

/*
 * ��������I2C_GPIO_Config
 * ����  ��I2C1 I/O����
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
 
void I2C2_Slave_Init(void)
{
	I2C2_GPIO_Config();
	I2C2_Mode_Configu();
}
 
//void I2C1_GPIO_Config(void)
//{
//  GPIO_InitTypeDef  GPIO_InitStructure; 

//	/* ʹ���� I2C1 �йص�ʱ�� */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);  
//    
//  /* PB6-I2C1_SCL��PB7-I2C1_SDA*/
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//}

void I2C2_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* ʹ���� I2C2 �йص�ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);  
    
  /* I2C2_SCL��SDA*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
 * ��������I2C_Configuration
 * ����  ��I2C ����ģʽ����
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void I2C2_Mode_Configu(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  /* I2C ���� */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;
  I2C_InitStructure.I2C_OwnAddress1 = I2C2_OWN_ADDRESS7<<1; // ��ַ�Ĵ���ֻ��7λ�������ǴӸ�λװ�صģ������ͽ�ȥ֮ǰ����Ҫ����һλ��
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
  /* ʹ�� I2C2 */
  I2C_Cmd(I2C2, ENABLE);

  /* I2C2 ��ʼ�� */
  I2C_Init(I2C2, &I2C_InitStructure);

   
}

