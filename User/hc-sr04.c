#include "hc-sr04.h"
#include "typedef.h"
#include "init.h"
#include "oled.h"
#include "detect.h"
#include "beep.h"


// 距离 = 高电平时间*声速（340M/S）/2
// 高电平时间 = 4m（最大距离） * 2 / 声速（340M/S）= 0.023529s = 23529.4us
void Get_Distance()
{
        __IO u16 TIM2_Val[2];
        __IO u16 i = 65535;
  
	//Clear_TIM2Counter();
	HIGH_TRIG();
	//TIM2_Delayxus(20);			// 20us
        usdelay_TIM4(20);
	LOW_TRIG();
	//while(!(1 == PORT_ECHO));
        while(!PORT_ECHO)
        {
              if(0 == (--i))
                    return;
        }
	ON_TIM2();
	//while(!(0 == PORT_ECHO));
        i = 65535;
        while(PORT_ECHO)
        {
              if(0 == (--i))
                    return;
        }
        TIM2_Value = TIM2Counter;
        OFF_TIM2();
        Clean_TIM2Counter();
        //DistanceData = DistanceData/101;
        //ultra_formula(DistanceData, TIM2_Value);
        //ON_LED_G();
        /*ON_TIM2();
	for(i=0; i<2; i++)
        {
              HIGH_TRIG();
              //TIM2_Delayxus(20);			// 20us
              usdelay_TIM4(20);
              LOW_TRIG();
              //ON_LED_G();
              //while(!(1 == PORT_ECHO));
              while(!PORT_ECHO);
              //ON_LED_G();
              //ON_TIM2();
              //while(!(0 == PORT_ECHO));
              Clean_TIM2Counter();
              while(PORT_ECHO);
              TIM2_Value = TIM2Counter;
              //OFF_TIM2();
              Clean_TIM2Counter();
              TIM2_Val[i] = TIM2_Value;
        }
        OFF_TIM2();
        //TIM2_Value = TIM2Counter;
        //DistanceData = TIM2Counter/58;	// 单位：cm
	DistanceData = ((TIM2_Val[0] + TIM2_Val[1]) >> 1)/101;*/
	//Flag_DetectData = SET;

        //ON_LED_G();
        //OLED_ShowNum(30, 6, DistanceData, 3, 16);
        /*if(Flag_ADC_Success == SET)
        {
              Flag_ADC_Success = RESET;
              OLED_ShowNum(30, 6, DistanceData, 3, 16);
        }*/
        //OLED_ShowNum(30, 4, TIM2_Value, 5, 16);
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
