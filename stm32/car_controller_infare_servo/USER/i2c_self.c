/********************************************************************************
 * 文件名  ：i2c_ee.c
 * 描述    ：i2c EEPROM(AT24C02)应用函数库         
 * 实验平台：野火STM32开发板
 * 硬件连接：-----------------
 *          |                 |
 *          |  PB6-I2C1_SCL	  |
 *          |  PB7-I2C1_SDA   |
 *          |                 |
 *           -----------------
 * 库版本  ：ST3.5.0
 * 作者    ：保留 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "i2c_self.h"

#define I2C_Speed              4000
//#define I2C1_OWN_ADDRESS7    0x0A
#define I2C2_OWN_ADDRESS7    0x25
#define I2C_PageSize           8			/* AT24C02每页有8个字节 */

uint16_t EEPROM_ADDRESS;

/*
 * 函数名：I2C_GPIO_Config
 * 描述  ：I2C1 I/O配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
 
void I2C2_Slave_Init(void)
{
	I2C2_GPIO_Config();
	I2C2_Mode_Configu();
}
 
//void I2C1_GPIO_Config(void)
//{
//  GPIO_InitTypeDef  GPIO_InitStructure; 

//	/* 使能与 I2C1 有关的时钟 */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);  
//    
//  /* PB6-I2C1_SCL、PB7-I2C1_SDA*/
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // 开漏输出
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//}

void I2C2_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* 使能与 I2C2 有关的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);  
    
  /* I2C2_SCL、SDA*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // 开漏输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
 * 函数名：I2C_Configuration
 * 描述  ：I2C 工作模式配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void I2C2_Mode_Configu(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  /* I2C 配置 */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;
  I2C_InitStructure.I2C_OwnAddress1 = I2C2_OWN_ADDRESS7<<1; // 地址寄存器只有7位，而且是从高位装载的，所以送进去之前，先要右移一位。
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
  /* 使能 I2C2 */
  I2C_Cmd(I2C2, ENABLE);

  /* I2C2 初始化 */
  I2C_Init(I2C2, &I2C_InitStructure);

   
}

