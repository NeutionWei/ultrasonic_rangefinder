//*****************************头文件声明****************************
#include "iostm8s103f3.h"
#include "typedef.h"
#include "key.h"
#include "init.h"
#include "beep.h"
#include "ultrasonic.h"
#include "display.h"
#include "oled.h"

__IO u32 Cnt_TIM1 = 0;

__IO FlagStatus Flag_MainLoop = RESET;


//*******************************主函数******************************

/* 1.系统初始化 */
/* 2.发射信号 -> 超声波信号 */
/* 3.检测信号 -> 读取距离值、OLED显示 */
/* 3.1数据异常操作 -> 亮LED灯 */
/* 3.2数据正常操作 -> 亮LED灯、响蜂鸣器 */
/* 4.报警调整 -> 按键 */

void main()
{
	Init_System();	// 系统初始化
	//Init_Data();	// 默认数据初始化
	Init_Disp();	// 显示初始化
	Delay(200);

	while(1)
	{
		if(Flag_MainLoop == SET)
		{
			Flag_MainLoop = RESET;
			Scan_Keys();	// 按键扫描
			Disp_Data();	// 显示数据
			Get_Distance();	// 获得超声波返回距离
			Detect_Data();	// 检查与处理数据
			Check_Alarm();	// 是否警报
			//ON_LED_Y();
			//TRIG = 1;
		}
	}
}

//*****************************中断程序****************************
#pragma vector = TIM1_OVR_UIF_vector    // 0x0D
__interrupt void TIM1_OVF_IRQHandler()	// 1us
{
	if(TIM1_SR1 & (1<<0))
	{
		TIM1_SR1 &= ~(1<<0);   	   // 清除中断标志位
		if(++Cnt_TIM1 >= 50)	   // 50us
		{
			Flag_MainLoop = SET;
			if(Cnt_TIM1 >= 100)
			{
				Cnt_TIM1 = 0;
			}
		}
		//SignalSend();
		//GetDistance();
	}
	else
	{
		TIM1_SR1 = 0x00;
		TIM1_SR2 = 0x00;
	}
}


void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
/*  while (1)
  {
  }*/
}
