/********************************************************
  * @file        	led.c
  * @author      	LGG
  * @version     	V1.0.0
  * @data        	2017年05月19日
  * @brief          LED文件
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
********************************************************/


/*inclides----------------------------------------------*/
#include "led.h"


/*definition--------------------------------------------*/



/*
	@brief			初始化LED的IO口
	@param			无
	@retval			无
 */
void LED_Init(void)
{
	PG_DDR |= 0x03;//将 PG0 PG1 口设为输出
	PG_CR1 |= 0x03;//将 PG0 PG1 口设为推挽
	PG_CR2 &= 0xfc;//将 PG0 PG1 口设为推挽
}


/***************以下是在16M频率下的延迟函数***************/
/*
	@brief			ms延迟函数
	@param			无
	@retval			无
*/
void delay_ms(unsigned int ms)//延迟函数，MS级别
{
	unsigned int x,y;
	for(x = ms;x>0;x--)
 {
		for(y = 1300;y>0;y--);
 }
}

/*
	@brief			us延迟函数  实测 0.82us
	@param			无
	@retval			无
*/
void delay_us(unsigned int us)
{
	while(us--);
}
/*********************************************************/

	
/**********以下是在系统上电默认2M频率下的延迟函数*********/
/*
	@brief			ms延迟函数
	@param			无
	@retval			无
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
	@brief			us延迟函数
	@param			无
	@retval			无
*/
/*void delay_us(unsigned int us) 
{
	//unsigned int i;
	while(us--);
}*/
/*********************************************************/