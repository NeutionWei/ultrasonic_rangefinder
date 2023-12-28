/********************************************************
  * @file        	main.c
  * @author      	LGG
  * @version     	V1.0.0
  * @data        	2017��06��9��
  * @brief       	������ - IIC����
  *
  *******************************************************
  *	@attention
  *
  *	PG0-->LED1		PG1-->LED2
  * Px_ODR-������ݼĴ���
  * Px_IDR-�������ݼĴ���
  * Px_DDR-���ݷ���Ĵ���
  * Px_CR1-���ƼĴ���1
  * Px_CR2-���ƼĴ���2
	*
	* I2C_CR1-���ƼĴ���1
	* I2C_CR2-���ƼĴ���2
	* I2C_FREQR-Ƶ�ʼĴ���
	* I2C_OARL-�����ַ�Ĵ���LSB
	* I2C_OARH-�����ַ�Ĵ���MSB
	* I2C_DR-���ݼĴ���
	* I2C_SR1-״̬�Ĵ���1
	* I2C_SR2-״̬�Ĵ���2
	* I2C_SR3-״̬�Ĵ���3
	* I2C_ITR-�жϼĴ���
	* I2C_CCRL-ʱ�ӿ��Ƶ�λ�Ĵ���
	* I2C_CCRH-ʱ�ӿ��Ƹ�λ�Ĵ���
	* I2C_TRISE-TRISE�Ĵ���---------ע�⣺д����Ĵ���ʱ��Ӧд I2C_TRISER
  *
********************************************************/


/*includes----------------------------------------------*/
#include<STM8S105C6.h>
#include "oled.h"
#include "led.h"


/*definition--------------------------------------------*/


/*
  *@brief  			������
  *@param       ��
  *@retval			��
 */
main()
{
	CLK_CKDIVR = 0x00;//f_HSI = f_HSI RC ���    f_CPU = f_MASTER    16M
	
	LED_Init();	//LED��ʼ��
	
	OLED_Init();	//OLED��ʼ��
	OLED_Clear();	//OLED����
	
	OLED_ShowString(30,2,"OLED TEST");//OLED��ʾ  OLED TEST

	OLED_ShowCHinese(16,0,0);	//OLED��ʾ  ��
	OLED_ShowCHinese(32,0,1);	//OLED��ʾ  ��
	OLED_ShowCHinese(48,0,2);	//OLED��ʾ  ��
	OLED_ShowCHinese(64,0,3);	//OLED��ʾ  ��
	OLED_ShowCHinese(80,0,4);	//OLED��ʾ  ��
	OLED_ShowCHinese(96,0,5);	//OLED��ʾ  ��
	
	while (1)
	{
		PG_ODR ^= 0x03;	//��� �� PG0 PG1 ��ȡ��
		delay_ms(300);	//�ӳ�300MS
	}
}


