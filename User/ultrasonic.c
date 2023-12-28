#include "ultrasonic.h"
#include "typedef.h"
#include "init.h"

__IO s16 DistanceData;
__IO s16 OutofDistance = 20;


__IO FlagStatus Flag_DetectData   = RESET;

extern __IO FlagStatus Flag_CheckAlarm;


void Get_Distance()
{
	//Clear_TIM2Counter();
	HIGH_TRIG();
	TIM2_Delayxus(20);			// 20us
	LOW_TRIG();
	while(!(1 == PORT_ECHO));
	ON_TIM2();
	while(!(0 == PORT_ECHO));
	OFF_TIM2();
	DistanceData = TIM2Counter/58;	// 单位：cm
	Clear_TIM2Counter();
	Flag_DetectData = SET;
}


/* 1.系统初始化 */
/* 2.发射信号 -> 超声波信号 */
/* 3.检测信号 -> 读取距离值、OLED显示 */
/* 3.1数据异常操作 -> 亮LED灯 */
/* 3.2数据正常操作 -> 亮LED灯、响蜂鸣器 */
/* 4.报警调整 -> 按键 */

void Detect_Data()
{
	if(RESET == Flag_DetectData)
	{
		// 未测量到数据
		ON_LED_Y();
		//Flag_OledDisplay = SET;
	}
	else
	{
		Flag_DetectData = RESET;
		
		if(DistanceData >= OutofDistance)
		{
			// 距离安全
			ON_LED_G();
			// 读数据，取数据，送显示数据
			// 打开显示标志位
		}
		else if((DistanceData >= 0) && (DistanceData < OutofDistance))
		{
			// 距离过近
			ON_LED_R();
			Flag_CheckAlarm = SET;
		}
		//Flag_OledDisplay = SET;
	}
}


/*void GetSignal()
{
	Flag_TRIG = SET;
}

void SendSignal()
{
	if(SET == Flag_TRIG)
	{
		Cnt_Level_ECHO = 0;
		HIGH_TRIG();
		if(++Cnt_Level_TRIG >= 20)	// 20us
		{
			LOW_TRIG();
			while(!PORT_ECHO);
			// 开定时器计数
			Flag_GetDistance = SET;
			Flag_TRIG = RESET;
		}
	}
}*/

/*void GetDistance()
{
	SendSignal();
	if(SET == Flag_GetDistance)	// 1us
	{
		if(1 == PORT_ECHO)
		{
			//++Cnt_Level_ECHO;
		}
		else
		{
			DistanceData = Cnt_Level_ECHO*340/2;
			// 关定时器计数
			// 清除计数值
			Flag_GetDistance = RESET;
		}
	}
}*/
