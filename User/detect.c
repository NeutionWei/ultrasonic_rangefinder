//*****************************头文件声明***************************
#include "iostm8s103f3.h"
#include "typedef.h"
#include "key.h"
#include "init.h"
#include "beep.h"
#include "hc-sr04.h"
#include "display.h"
#include "oled.h"
#include "ds18b20.h"
#include "detect.h"

/* 1.系统初始化 */
/* 2.发射信号 -> 超声波信号 */
/* 3.检测信号 -> 读取距离值、OLED显示 */
/* 3.1数据异常操作 -> 亮LED灯 */
/* 3.2数据正常操作 -> 亮LED灯、响蜂鸣器 */
/* 4.报警调整 -> 按键 */

//__IO FlagStatus Flag_DetectData   = RESET;
//__IO FlagStatus Flag_ADC_Success  = RESET;
__IO FlagStatus Flag_dis_mistake  = RESET; // 距离数据出错标志
__IO FlagStatus Flag_dis_normal   = RESET; // 距离数据正常标志
__IO FlagStatus Flag_dis_abnormal = RESET; // 距离数据过近标志

__IO u8 curFlag_dis = MISTAKE;
__IO u8 oldFlag_dis = MISTAKE;
__IO u8 cnt_mistake,cnt_normal,cnt_abnormal;

__IO u16 DistanceData;
__IO u16 OutofDistance = 20;


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
                return -1;
	}
        return -1;
}



void Detect_Data()
{
        int ret;
        static unsigned int cnt_detect;

        if(++cnt_detect >= DETECT_MAX)
        {
          ret = Ave_Process();
          if(-1 == ret)
          {
            // 未测量到数据
            //if(>=)
            Flag_dis_mistake = SET;
          }
          else
          {
            if(DistanceData >= OutofDistance)
            {
              // 距离安全
              Flag_dis_normal = SET;
            }
            else if((DistanceData >= 5) && (DistanceData < OutofDistance))
            {
              // 距离过近
              Flag_dis_abnormal = SET;
            }
          }
        }
          
	/*if(RESET == Flag_DetectData)
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
	}*/
}