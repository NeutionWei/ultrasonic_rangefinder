#ifndef	_INIT_H
#define _INIT_H

#include "typedef.h"
#include "iostm8s103f3.h"


//****************************端口引脚宏定义***************************
#define PORT_SCL		(PA_ODR_ODR4)		// I2C_SCL
#define PORT_SDA		(PA_ODR_ODR5)		// I2C_SDA
#define PORT_TRIG		(PC_ODR_ODR5)		// OUTPUT
#define PORT_ECHO		(PC_IDR_IDR6)		// INPUT
#define PORT_BEEP		(PD_ODR_ODR4)		// OUTPUT
#define PORT_LED_Y		(PD_ODR_ODR3)		// OUTPUT
#define PORT_LED_G		(PD_ODR_ODR2)		// OUTPUT
#define PORT_LED_R		(PC_ODR_ODR7)		// OUTPUT
#define PORT_K_U		(PC_IDR_IDR4)		// INPUT
#define PORT_K_D		(PC_IDR_IDR3)		// INPUT


//#define PA3

//****************************LED打开与关闭宏函数***************************
#define	ON_LED_Y()		(PORT_LED_Y=1)
#define	ON_LED_G()		(PORT_LED_G=1)
#define	ON_LED_R()		(PORT_LED_R=1)
#define	OFF_LED_Y()		(PORT_LED_Y=0)
#define	OFF_LED_G()		(PORT_LED_G=0)
#define	OFF_LED_R()		(PORT_LED_R=0)
                        
#define	LOW_TRIG()		(PORT_TRIG=0)
#define	HIGH_TRIG()		(PORT_TRIG=1)

//#define	ON_TIMER()		TIM4_CR1=0x01

#define	TIM2Counter ((TIM2_CNTRH<<8) | TIM2_CNTRL)// TIM2计数值
#define ON_TIM2()    {TIM2_CR1  |=  (1<<0);}// 开TIM2
#define OFF_TIM2()   {TIM2_CR1  &= ~(1<<0);}// 关TIM2
#define Clean_TIM2Counter() {TIM2_CNTRH = 0; TIM2_CNTRL = 0;}// 清零TIM2计数器

void Init_Clock();
void Init_GPIO();
void Init_TIM1();
void Init_TIM4();
//void ON_TIM2();
//void OFF_TIM2();
//void Clean_TIM2Counter();
void Init_TIM2();
void Init_System();
void Delay(u8 x);
//void TIM2_Delayxus(u8 x);
void Init_Beep();
void usdelay_TIM4(int us);
//void sdelay_TIM4(int s);


#endif /* _INIT_H */

