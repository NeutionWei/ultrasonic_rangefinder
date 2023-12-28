#include "init.h"


void Init_Clock()
{
	// CLOCK初始化 -> stm8s.pdf p90
	CLK_ICKR |= (1<<0);				// 使能内部高速时钟  
	while(!(CLK_ICKR | (1<<1)));	// 等待准备就绪  
	CLK_SWCR &= ~((1<<2) | (1<<3));	// 时钟切换中断禁止并清除中断标志  
	CLK_SWR   = 0xE1;				// 时钟选择为HSI  
	while(CLK_SWCR & (1<<0));		// 等待时钟切换慢的结束  
	CLK_SWCR |= (1<<0);				// 使能时钟切换	
	while(CLK_CMSR != 0xE1);		// 等待系统时钟切换到0xE1
	CLK_CKDIVR = 0x00;				// 设置时钟预分频,设置为fmaster = fclock = 16MHz
	CLK_CCOR &= ~(1<<0);			// 禁止CCO输出
}

void Init_GPIO()
{
	// I/O初始化 -> stm8s.pdf p112
	PC_DDR = (1<<5) | (1<<7);
	PD_DDR = (1<<2) | (1<<3) | (1<<4);
	PC_CR1 = (1<<7);
	PD_CR1 = (1<<2) | (1<<3) | (1<<4);
	//PD_CR2
}

void Init_Beep()
{
	// Beeper初始化 -> stm8s.pdf p122
	// 00: fLS/(8 x BEEPDIV) kHz output
	// 01: fLS/(4 x BEEPDIV) kHz output
	// 1x: fLS/(2 x BEEPDIV) kHz output
	BEEP_CSR_BEEPDIV = 0x0E;	// 校验时钟 128k/16 = 8k
	BEEP_CSR_BEEPSEL = 1;		// 2k
}

void Init_TIM1()
{
	// TIM1初始化 -> stm8s.pdf p188
	CLK_PCKENR1 |= (1<<7);  	// 打开TIM1时钟 = fmaster
	asm("sim");             	// 关全局中断
	TIM1_PSCRH = 0; 			// fCK_PSC / (PSCR[15:0]+1)
	TIM1_PSCRL = 15;    		// 1分频，定时器时钟等于系统时钟=16MHz/16=1MHz
	TIM1_ARRH  = 0;        		// 1us溢出
	TIM1_ARRL  = 1;
	TIM1_CNTRH = 0;				// 清除计数器
    TIM1_CNTRL = 0;

	TIM1_IER  |= (1<<0);  			 // 允许更新中断
	TIM1_EGR  |= (1<<0);  			 // 产生更新事件
	TIM1_CR1  |= ((1<<7) | (1<<0));  // 开计数器
	asm("rim");        				 // 开全局中断
}

void ON_TIM2()
{
	TIM2_CR1  |= (1<<0);  // 开计数器	
}

void OFF_TIM2()
{
	TIM2_CR1  &= ~(1<<0);  // 关计数器	
}

void Clear_TIM2Counter()
{
	TIM2_CNTRH = 0;				// 清除计数器
    TIM2_CNTRL = 0;
}


void Init_TIM2()
{
	// TIM2初始化 -> stm8s.pdf p188
	CLK_PCKENR1 |= (1<<5);  	// 打开TIM2时钟 = fmaster
	//asm("sim");             	// 关全局中断
	TIM2_PSCR  = 0;				// fCK_CNT = fCK_PSC / 2^(PSC[3:0]).
	TIM2_ARRH  = 0xFF;        	// 65535us溢出
	TIM2_ARRL  = 0xFF;
	TIM2_CNTRH = 0;				// 清除计数器
    TIM2_CNTRL = 0;
	TIM2_CR1  |= (1<<7); 
	//TIM2_IER  |= (1<<0);  			 // 允许更新中断
	//TIM2_EGR  |= (1<<0);  			 // 产生更新事件
	//TIM2_CR1  |= ((1<<7) | (1<<0));  // 开计数器
	//asm("rim");        				 // 开全局中断
}

void Init_System()
{
	Init_Clock();
	Init_GPIO();
	Init_TIM1();
	Init_TIM2();
	/* LED初始化 */
	/* 按键初始化 */
	/* OLED初始化 */
	/* HC-SR04初始化 */
	/* 蜂鸣器初始化 */
	/* DS18B20初始化 */
}

void Delay(__IO u8 x)
{
	u8 i = 0;
	
	while(x--)
	{
		while(--i)
		{
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
		}
	}
}

void TIM2_Delayxus(u8 x)	// 256us以内
{
	ON_TIM2();
	while(!(TIM2_CNTRL >= x));
	OFF_TIM2();
	Clear_TIM2Counter();
}

/*void delay_us(unsigned int us)
{
	while(us--);
}*/

