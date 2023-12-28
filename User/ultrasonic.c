#include "ultrasonic.h"
#include "typedef.h"
#include "init.h"
#include "oled.h"


__IO u16 TIM2_Value;
__IO u16 DistanceData;
__IO u16 OutofDistance = 20;


__IO FlagStatus Flag_DetectData   = RESET;
__IO FlagStatus Flag_ADC_Success  = RESET;

extern __IO FlagStatus Flag_CheckAlarm;

// 平均值计算
int Ave_Process()
{
	static volatile int   adc_exist;
	volatile unsigned int adc_data;
	static volatile unsigned int  adc_max = 0;
	static volatile unsigned int  adc_min = 0;
	static volatile unsigned int  adc_sum = 0;
	static volatile unsigned char adc_cnt = 0;
        static volatile unsigned int  adc_ave = 0;

	if(0 != TIM2_Value)
	{
		/* 记录TIM2的数值 */
		adc_data  = TIM2_Value;
		
		
		/* 找出最大最小值 */
		if(!adc_exist)
		{
			adc_exist = 1;
			adc_max = adc_data;
			adc_min = adc_data;
		}
		else if(adc_data > adc_max)
			adc_max = adc_data;
		else if(adc_data < adc_min)
			adc_min = adc_data;
			
		adc_sum +=  adc_data;
		if(++adc_cnt >= 6)
		{
			adc_sum -= adc_max;
			adc_sum -= adc_min;
			
                        adc_ave = (adc_sum >> 2);
			
                        /*ultra_formula(DistanceData, adc_ave);
                        Dis[0] = DistanceData/100;
                        Dis[1] = DistanceData%100/10;
                        Dis[2] = DistanceData%10;
                        OLED_ShowNum(15, 6, Dis[0], 1, 16);
                        OLED_ShowNum(25, 6, Dis[1], 1, 16);
                        OLED_ShowNum(35, 6, Dis[2], 1, 16);*/
                        
			if(adc_max <= (adc_min+50))
                        {
                                ultra_formula(DistanceData, adc_ave);
                                
                                adc_sum = 0;
                                adc_max = 0;
                                adc_min = 0;
                                adc_cnt = 0;
                                adc_exist = 0;
                                return 0;
                                /*Dis[0] = DistanceData/100;
                                Dis[1] = DistanceData%100/10;
                                Dis[2] = DistanceData%10;
                                OLED_ShowNum(15, 6, Dis[0], 1, 16);
                                OLED_ShowNum(25, 6, Dis[1], 1, 16);
                                OLED_ShowNum(35, 6, Dis[2], 1, 16);*/
				//Flag_ADC_Success = SET;
			}
			adc_sum = 0;
                        adc_max = 0;
                        adc_min = 0;
                        adc_cnt = 0;
                        adc_exist = 0;	
			
                        return -1;
		}
	}
	else
	{
		adc_sum = 0;
		adc_min = 0;
		adc_max = 0;
		adc_cnt = 0;
//		adc_exist = 0;
	}

}



// 距离 = 高电平时间*声速（340M/S）/2
// 高电平时间 = 4m（最大距离） * 2 / 声速（340M/S）= 0.023529s = 23529.4us
void Get_Distance()
{
        int ret;
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
        i = 35536;
        while(PORT_ECHO)
        {
              if(0 == (--i))
                    return;
        }
        TIM2_Value = TIM2Counter;
        Clean_TIM2Counter();
	OFF_TIM2();
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
        ret = Ave_Process();
        if(-1 == ret)
              Flag_DetectData = RESET;
        else
              Flag_DetectData = SET;
        //ON_LED_G();
        //OLED_ShowNum(30, 6, DistanceData, 3, 16);
        /*if(Flag_ADC_Success == SET)
        {
              Flag_ADC_Success = RESET;
              OLED_ShowNum(30, 6, DistanceData, 3, 16);
        }*/
        //OLED_ShowNum(30, 4, TIM2_Value, 5, 16);
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
                OFF_LED_G();
                OFF_LED_R();
		//Flag_OledDisplay = SET;
	}
	else
	{
		Flag_DetectData = RESET;
		
		if(DistanceData >= OutofDistance)
		{
			// 距离安全
			ON_LED_G();
                        OFF_LED_R();
                        OFF_LED_Y();
			// 读数据，取数据，送显示数据
			// 打开显示标志位
		}
		else if((DistanceData >= 5) && (DistanceData < OutofDistance))
		{
			// 距离过近
			ON_LED_R();
                        OFF_LED_G();
                        OFF_LED_Y();
			//Flag_CheckAlarm = SET;
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
