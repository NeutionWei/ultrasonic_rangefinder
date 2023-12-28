/********************************************************
  * @file        	main.c
  * @author      	LGG
  * @version     	V1.0.0
  * @data        	2017年06月9日
  * @brief       	主函数 - IIC工程
  *
  *******************************************************
  *	@attention
  *
  *	PG0-->LED1		PG1-->LED2
  * Px_ODR-输出数据寄存器
  * Px_IDR-输入数据寄存器
  * Px_DDR-数据方向寄存器
  * Px_CR1-控制寄存器1
  * Px_CR2-控制寄存器2
	*
	* I2C_CR1-控制寄存器1
	* I2C_CR2-控制寄存器2
	* I2C_FREQR-频率寄存器
	* I2C_OARL-自身地址寄存器LSB
	* I2C_OARH-自身地址寄存器MSB
	* I2C_DR-数据寄存器
	* I2C_SR1-状态寄存器1
	* I2C_SR2-状态寄存器2
	* I2C_SR3-状态寄存器3
	* I2C_ITR-中断寄存器
	* I2C_CCRL-时钟控制低位寄存器
	* I2C_CCRH-时钟控制高位寄存器
	* I2C_TRISE-TRISE寄存器---------注意：写这个寄存器时，应写 I2C_TRISER
  *
********************************************************/


/*includes----------------------------------------------*/
#include<STM8S105C6.h>
#include "oled.h"
#include "led.h"


/*definition--------------------------------------------*/


/*
  *@brief  			主函数
  *@param       无
  *@retval			无
 */
main()
{
	CLK_CKDIVR = 0x00;//f_HSI = f_HSI RC 输出    f_CPU = f_MASTER    16M
	
	LED_Init();	//LED初始化
	
	OLED_Init();	//OLED初始化
	OLED_Clear();	//OLED清屏
	
	OLED_ShowString(30,2,"OLED TEST");//OLED显示  OLED TEST

	OLED_ShowCHinese(16,0,0);	//OLED显示  技
	OLED_ShowCHinese(32,0,1);	//OLED显示  新
	OLED_ShowCHinese(48,0,2);	//OLED显示  电
	OLED_ShowCHinese(64,0,3);	//OLED显示  子
	OLED_ShowCHinese(80,0,4);	//OLED显示  科
	OLED_ShowCHinese(96,0,5);	//OLED显示  技
	
	while (1)
	{
		PG_ODR ^= 0x03;	//异或 对 PG0 PG1 口取反
		delay_ms(300);	//延迟300MS
	}
}


