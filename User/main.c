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

//__IO u8 cnt;
__IO u8 Cnt_TIM1 = 0;
__IO u8 Cnt_MainLoop = 0;
__IO u8 Cnt_Alarm = 0;
__IO FlagStatus Flag_MainLoop = RESET;
//__IO u8 Flag_MainLoop = 0;
//__IO u8 isr = 0;
//__IO u16 cnt = 0;




//*******************************主函数*****************************

/* 1.系统初始化*/
/* 2.发射信号 -> 超声波信号*/
/* 3.检测信号-> 读取距离值、OLED显示 */
/* 3.1数据异常操作 -> 亮LED灯*/
/* 3.2数据正常操作 -> 亮LED灯、响蜂鸣响*/
/* 4.报警调整 -> 按键 */

int main(void)
{
  //init();
  Init_Clock();
  Init_GPIO();
  Init_TIM1();
  Init_TIM2();
  Init_TIM4();
  Init_Beep();
  Init_Disp();
  Delay(200);
  //ON_LED_Y();
  while(1)
  {
      //sdelay_TIM4(500);
      //OLED_ShowNum(30, 4, TIM4_CNTR, 4, 16);
      //usdelay_TIM4(50);
      //msdelay_TIM4(30);
      //ON_LED_Y();
      //ds18b20_test();
      //GetTemperature();
      //DispTemperature();
      //Temp = readTemp();
      //OLED_ShowNum(30, 4, Temp, 4, 16);
      //DS18B20_ReadTemperature();
      if(Flag_MainLoop == SET)
      {
              Flag_MainLoop = RESET;  
              Scan_Keys();	// 按键扫描
              Disp_Data();	// 显示数据
              Get_Distance();	// 获得超声波模块的距离值
              Get_Temperature(); //获得温度传感器的温度值
              Detect_Data();	// 检查与处理数据
              //Check_Alarm();	// 是否警报

              
              //Temp = readTemp();
              //tem1 = Temp/10;
              //tem2 = Temp%10;
              //OLED_ShowNum(30, 4, tem1, 1, 16);
              //OLED_ShowNum(45, 4, tem2, 1, 16);
              //Scan_Keys();	// 按键扫描
              //Disp_Data();	// 显示数据
              //Get_Distance();	// 获得超声波返回距离
              //ds18b20_test();
              /*if(++cnt >= 3)
              {
                  cnt = 0;
                  Get_Distance();	// 获得超声波返回距离
              }*/
              //Detect_Data();	// 检查与处理数据
              //Check_Alarm();	// 是否警报
              //ON_LED_Y();
              
              //TRIG = 1;
      }    
  }
}

//*****************************中断程序****************************
#pragma vector = TIM1_OVR_UIF_vector    // 0x0D
__interrupt void TIM1_OVF_IRQHandler()	// 125us
{
	if(TIM1_SR1 & (1<<0))
	{
                //ON_LED_Y();
		TIM1_SR1 &= ~(1<<0);   	   // 清除中断标志位
                TIM1_SR2 &= ~(1<<0);
		if(++Cnt_TIM1 >= 8)	   // 1ms
		{
                        Cnt_TIM1 = 0;
                        //ON_LED_Y();
                        if(++Cnt_Alarm >= 5)
                        {
                          Cnt_Alarm = 0;
                          Check_Alarm();
                        }
                        if(++Cnt_MainLoop >= 20)        //20ms
                        {
                          Cnt_MainLoop  = 0;
                          Flag_MainLoop = SET;
                          //ON_LED_Y();
                          //ON_LED_G();
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
        /*TIM1_SR1 = 0x00;
   	//TIM1_SR2 = 0x00;

        if(++Cnt_TIM1 >= 50)	   // 50us
        {
                Cnt_TIM1 = 0;
                //ON_LED_Y();
                if(++Cnt_MainLoop >= 400)
                {
                  Flag_MainLoop = 1;
                  ON_LED_Y();
                  ON_LED_G();
                }
        }
        return;*/
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



