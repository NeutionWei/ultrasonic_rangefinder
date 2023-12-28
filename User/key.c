#include "key.h"
#include "typedef.h"
//#include "iostm8s103f3.h"
#include "init.h"
#include "ultrasonic.h"

//#define		key_input	  ((PORT_K_U<<1) | PORT_K_D)
#define 	key_state_0   0
#define		key_state_1   1
#define		key_state_2   2
#define	 	key_state_3   3

#define		KEY_INCRE	(1<<1)
#define		KEY_DECRE	(1<<0)

extern __IO s16 OutofDistance;


void Scan_Keys()
{
	static u16 key_state = 0;
	u8 key_press;
	u8 key_input;
	//u8 key_return = 0;	

	key_input  = PORT_K_U;
	key_input  = key_input<<1;
	key_input |= PORT_K_D;
	key_press = key_input;					// 读按键I/O电平
	switch (key_state)
	{
		case key_state_0:					// 按键初始态
			if (key_press) key_state = key_state_1; // 键被按下，状态转换到键确认态
			break;
			
		case key_state_1:					// 按键确认态
			if (key_press)
			{
				if(key_press & KEY_INCRE)
				{
					if(OutofDistance <= OutofDistance_Up)
						OutofDistance += 5;
				}
				else if(key_press & KEY_DECRE)
				{
					if(OutofDistance >= OutofDistance_Down)
						OutofDistance -= 5;
				}
			}
			else
				key_state = key_state_0;	// 按键已抬起，转换到按键初始态
			break;
		case key_state_2:
			if (!key_press)
				key_state = key_state_0;	// 按键已释放，转换到按键初始态
			break;
/*		case key_state_3:
			if (!key_press)
				key_state = key_state_0; //按键已释放，转换到按键初始态
			
			break;*/
		default:break;
	}	
	//return key_return;
}

