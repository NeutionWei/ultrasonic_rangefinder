#ifndef	_DISPLAY_H
#define _DISPLAY_H

#include "typedef.h"
#include "iostm8s103f3.h"
#include "init.h"

//****************************LED打开与关闭宏函数***************************
#define	ON_LED_Y()		(PORT_LED_Y=1)
#define	ON_LED_G()		(PORT_LED_G=1)
#define	ON_LED_R()		(PORT_LED_R=1)
#define	OFF_LED_Y()		(PORT_LED_Y=0)
#define	OFF_LED_G()		(PORT_LED_G=0)
#define	OFF_LED_R()		(PORT_LED_R=0)



void Init_Disp();
void Disp_Data();




#endif /* _DISPLAY_H */


