#include "display.h"
#include "oled.h"

void Init_Disp()
{
	OLED_Init();
	OLED_Clear();	// OLED清屏
}


void Disp_Data()
{
	OLED_ShowString(30,2,"OLED TEST");//OLED显示  OLED TEST
}
