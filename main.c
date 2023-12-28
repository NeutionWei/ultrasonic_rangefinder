//*****************************ͷ�ļ�����***************************
#include "iostm8s103f3.h"
#include "typedef.h"
#include "key.h"
#include "init.h"
#include "beep.h"
#include "ultrasonic.h"
#include "display.h"
#include "oled.h"
#include "ds18b20.h"

__IO u8 cnt;
__IO u8 Cnt_TIM1 = 0;
__IO u8 Cnt_MainLoop = 0;
__IO u8 Cnt_Alarm = 0;
__IO FlagStatus Flag_MainLoop = RESET;
//__IO u8 Flag_MainLoop = 0;
//__IO u8 isr = 0;
//__IO u16 cnt = 0;

//*******************************������*****************************

/* 1.ϵͳ��ʼ��*/
/* 2.�����ź� -> �������ź�*/
/* 3.����ź�-> ��ȡ����ֵ��OLED��ʾ */
/* 3.1�����쳣���� -> ��LED��*/
/* 3.2������������ -> ��LED�ơ��������*/
/* 4.�������� -> ���� */

void main(void)
{
	/*Init_System();	// ϵͳ��ʼ��
	//Init_Data();	// Ĭ�����ݳ�ʼ��
	//Init_Disp();	// ��ʾ��ʼ��
	Delay(200);

	while(1)
	{
		if(Flag_MainLoop == SET)
		{
			Flag_MainLoop = RESET;
			Scan_Keys();	// ����ɨ��
			Disp_Data();	// ��ʾ����
			Get_Distance();	// ��ó��������ؾ���
			Detect_Data();	// ����봦������
			Check_Alarm();	// �Ƿ񾯱�
			//ON_LED_Y();
			//TRIG = 1;
		}
	}*/
        Init_Clock();
        Init_GPIO();
        Init_TIM1();
        Init_TIM2();
        Init_TIM4();
        Init_Beep();
        Init_Disp();
        
        LOW_TRIG();
        //Clean_TIM2Counter();
        Delay(200);
        while(1)
        {
                //sdelay_TIM4(500);
                //OLED_ShowNum(30, 4, TIM4_CNTR, 4, 16);
                //usdelay_TIM4(50);
                //msdelay_TIM4(30);
                //ON_LED_Y();
		if(Flag_MainLoop == SET)
		{
			Flag_MainLoop = RESET;
			Scan_Keys();	// ����ɨ��
			//Disp_Data();	// ��ʾ����
			Get_Distance();	// ��ó��������ؾ���
                        /*if(++cnt >= 3)
                        {
                            cnt = 0;
                            Get_Distance();	// ��ó��������ؾ���
                        }*/
			//Detect_Data();	// ����봦������
			//Check_Alarm();	// �Ƿ񾯱�
                        ON_LED_Y();
                        
			//TRIG = 1;
		}       
        }
}

//*****************************�жϳ���****************************
#pragma vector = TIM1_OVR_UIF_vector    // 0x0D
__interrupt void TIM1_OVF_IRQHandler()	// 125us
{
	if(TIM1_SR1 & (1<<0))
	{
                //ON_LED_Y();
		TIM1_SR1 &= ~(1<<0);   	   // ����жϱ�־λ
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
