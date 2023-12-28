#include "key.h"
#include "typedef.h"
#include "beep.h"
//#include "iostm8s103f3.h"
#include "init.h"
#include "hc-sr04.h"

//#define		key_input	  ((PORT_K_U<<1) | PORT_K_D)
#define 	key_state_0   0
#define		key_state_1   1
#define		key_state_2   2
#define	 	key_state_3   3

#define		KEY_INCRE	(1<<1)
#define		KEY_DECRE	(1<<0)

extern __IO s16 OutofDistance;
//extern volatile unsigned int val;

void Scan_Keys()
{
	static u16 key_state = 0;
	u8 key_press;
	u8 key_input;
	//u8 key_return = 0;	
        
	key_input  = !PORT_K_U;
	key_input  = key_input<<1;
	key_input |= (!PORT_K_D);
	key_press  = key_input;					// 读按键I/O电平
        //ON_LED_R();
	switch (key_state)
	{
		case key_state_0:					// 按键初始态
			//if (key_press) key_state = key_state_1; // 键被按下，状态转换到键确认态
                        if (key_press)
                        {
                          key_state = key_state_1;
                          //ON_LED_R();
                        }
			break;
			
		case key_state_1:					// 按键确认态
			if (key_press)
			{
				if(key_press & KEY_INCRE)
				{
                                        //ON_LED_G();
                                        //OFF_LED_R();
                                        //Flag_CheckAlarm = SET;
                                        //val += 5;
					if(OutofDistance <= OutofDistance_Up)
						OutofDistance += 5;
				}
				else if(key_press & KEY_DECRE)
				{
                                        //ON_LED_R();
                                        //OFF_LED_G();
					if(OutofDistance >= OutofDistance_Down)
						OutofDistance -= 5;
				}
                                key_state = key_state_2;
			}
			else
				key_state = key_state_0;	// 按键已抬起，转换到按键初始态
			break;
		case key_state_2:
			if (!key_press)
                        {
                                //ON_LED_R();
                                //Flag_CheckAlarm = RESET;
				key_state = key_state_0;	// 按键已释放，转换到按键初始态
                        }
			break;
/*		case key_state_3:
			if (!key_press)
				key_state = key_state_0; //按键已释放，转换到按键初始态
			
			break;*/
		default:break;
	}	
	//return key_return;
}

