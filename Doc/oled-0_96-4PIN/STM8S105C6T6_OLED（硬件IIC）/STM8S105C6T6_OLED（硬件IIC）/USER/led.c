/********************************************************
  * @file        	led.c
  * @author      	LGG
  * @version     	V1.0.0
  * @data        	2017��05��19��
  * @brief          LED�ļ�
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
********************************************************/


/*inclides----------------------------------------------*/
#include "led.h"


/*definition--------------------------------------------*/



/*
	@brief			��ʼ��LED��IO��
	@param			��
	@retval			��
 */
void LED_Init(void)
{
	PG_DDR |= 0x03;//�� PG0 PG1 ����Ϊ���
	PG_CR1 |= 0x03;//�� PG0 PG1 ����Ϊ����
	PG_CR2 &= 0xfc;//�� PG0 PG1 ����Ϊ����
}


/***************��������16MƵ���µ��ӳٺ���***************/
/*
	@brief			ms�ӳٺ���
	@param			��
	@retval			��
*/
void delay_ms(unsigned int ms)//�ӳٺ�����MS����
{
	unsigned int x,y;
	for(x = ms;x>0;x--)
 {
		for(y = 1300;y>0;y--);
 }
}

/*
	@brief			us�ӳٺ���  ʵ�� 0.82us
	@param			��
	@retval			��
*/
void delay_us(unsigned int us)
{
	while(us--);
}
/*********************************************************/

	
/**********��������ϵͳ�ϵ�Ĭ��2MƵ���µ��ӳٺ���*********/
/*
	@brief			ms�ӳٺ���
	@param			��
	@retval			��
*/
/*void delay_ms(unsigned int ms)
{
	unsigned int x,y;
	for(x = ms;x>0;x--)
 {
		for(y = 156;y>0;y--);
 }
}
*/
/*
	@brief			us�ӳٺ���
	@param			��
	@retval			��
*/
/*void delay_us(unsigned int us) 
{
	//unsigned int i;
	while(us--);
}*/
/*********************************************************/