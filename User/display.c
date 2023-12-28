#include "display.h"
#include "oled.h"
#include "iic.h"

//volatile unsigned int val = 5;
extern __IO u16 DistanceData;
extern __IO u16 OutofDistance;
__IO u8 OutDis[3];
__IO u8 Dis[3];

void Init_Disp()
{
        IIC_Init();
	OLED_Init();
	OLED_Clear();	// OLED清屏
}


void Disp_Data()
{
	//OLED_ShowString(30, 2, "OLED TEST");//OLED显示  OLED TEST
        //OLED_ShowCHinese();
        OutDis[0] = OutofDistance/100;
        OutDis[1] = OutofDistance%100/10;
        OutDis[2] = OutofDistance%10;
        
        OLED_ShowNum(15, 0, OutDis[0], 1, 16);
        OLED_ShowNum(25, 0, OutDis[1], 1, 16);
        OLED_ShowNum(35, 0, OutDis[2], 1, 16);
        
        Dis[0] = DistanceData/100;
        Dis[1] = DistanceData%100/10;
        Dis[2] = DistanceData%10;
        
        OLED_ShowNum(15, 2, Dis[0], 1, 16);
        OLED_ShowNum(25, 2, Dis[1], 1, 16);
        OLED_ShowNum(35, 2, Dis[2], 1, 16);
        //OLED_ShowNum(30, 4, val, 2, 16);
        //OLED_ShowString(30,4,"NEUTION WEI");
}
