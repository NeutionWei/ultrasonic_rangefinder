#include "display.h"
#include "oled.h"
#include "iic.h"
#include "ds18b20.h"
#include "detect.h"

//volatile unsigned int val = 5;
//extern __IO u16 DistanceData;
//extern __IO u16 OutofDistance;
//__IO u8 cnt_mistake;
__IO u8 OutDis[3];
__IO u8 Dis[3];

enum{
  MISTAKE,
  NORMAL,
  ABNORMAL,
};

void Init_Disp()
{
        IIC_Init();
	OLED_Init();
	OLED_Clear();	// OLED清屏

        OLED_ShowString(0, 0, "Temperatures:");
        OLED_ShowString(0, 2, "Threshold:");
        OLED_ShowString(0, 4, "Distances:");
}


void Disp_Data()
{
        static __IO u8 curFlag_dis = MISTAKE;
        static __IO u8 oldFlag_dis = MISTAKE;
        static __IO u8 cnt_mistake;
	//OLED_ShowString(30, 2, "OLED TEST");//OLED显示  OLED TEST
        //OLED_ShowCHinese();
        if(Flag_dis_mistake == SET)
        {
          Flag_dis_mistake = RESET;
          // 连续采集判断算法
          curFlag_dis = MISTAKE;
          if(curFlag_dis == oldFlag_dis)
          {
            if(++cnt_mistake >= MISTAKE_MAX)
            {
              cnt_mistake = 0;
              // 距离值不显示 
              // 亮黄灯，关其他灯
              //OLED_Clear();	// OLED清屏
              OLED_ShowString(0, 4, "Distances:");
              OLED_ShowString(90, 4, "---");
              ON_LED_Y();
              OFF_LED_G();
              OFF_LED_R();
              //OLED_ShowNum(90,  4, Dis[0], 1, 16);
              //OLED_ShowNum(98,  4, Dis[1], 1, 16);
              //OLED_ShowNum(106, 4, Dis[2], 1, 16); 
            }
          }
          else
            cnt_mistake = 0;
          oldFlag_dis = curFlag_dis;         
        }
        else if(Flag_dis_normal == SET)
        {
          Flag_dis_normal = RESET;
          oldFlag_dis = NORMAL;
          // 距离值显示
          // 亮绿灯，关其他灯
          //OLED_Clear();	// OLED清屏
          Dis[0] = DistanceData/100;
          Dis[1] = DistanceData%100/10;
          Dis[2] = DistanceData%10;
          OLED_ShowString(0, 4, "Distances:");
          OLED_ShowNum(90,  4, Dis[0], 1, 16);
          OLED_ShowNum(98,  4, Dis[1], 1, 16);
          OLED_ShowNum(106, 4, Dis[2], 1, 16);  
          OFF_LED_Y();
          ON_LED_G();
          OFF_LED_R();
        }
        else if(Flag_dis_abnormal == SET)
        {
          Flag_dis_abnormal = RESET;
          oldFlag_dis = ABNORMAL;
          // 距离值显示
          // 亮红灯，关其他灯
          //OLED_Clear();	// OLED清屏
          Dis[0] = DistanceData/100;
          Dis[1] = DistanceData%100/10;
          Dis[2] = DistanceData%10;
          OLED_ShowString(0, 4, "Distances:");
          OLED_ShowNum(90,  4, Dis[0], 1, 16);
          OLED_ShowNum(98,  4, Dis[1], 1, 16);
          OLED_ShowNum(106, 4, Dis[2], 1, 16);  
          OFF_LED_Y();
          OFF_LED_G();
          ON_LED_R();
        }
        
        OutDis[0] = OutofDistance/100;
        OutDis[1] = OutofDistance%100/10;
        OutDis[2] = OutofDistance%10;
        OLED_ShowString(0, 2, "Threshold:");
        OLED_ShowNum(90,  2, OutDis[0], 1, 16);
        OLED_ShowNum(98,  2, OutDis[1], 1, 16);
        OLED_ShowNum(106, 2, OutDis[2], 1, 16);        
        
        //OLED_ShowNum(15, 0, OutDis[0], 1, 16);
        //OLED_ShowNum(25, 0, OutDis[1], 1, 16);
        //OLED_ShowNum(35, 0, OutDis[2], 1, 16);
        
        
        //OLED_ShowNum(15, 2, Dis[0], 1, 16);
        //OLED_ShowNum(25, 2, Dis[1], 1, 16);
        //OLED_ShowNum(35, 2, Dis[2], 1, 16);
        OLED_ShowString(0, 0, "Temperatures:");
        OLED_ShowNum(103, 0, temp%256, 2, 16);
        

        
        //OLED_ShowNum(30, 4, val, 2, 16);
        //OLED_ShowString(30,4,"NEUTION WEI");
        //OLED_ShowString(0, 6, "--");
}
