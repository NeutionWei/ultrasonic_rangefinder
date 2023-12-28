#include "key.h"
#include "init.h"
#include "beep.h"
//#include "display.h"
#include "typedef.h"
#include "ultrasonic.h"
#include "iostm8s103f3.h"

__IO FlagStatus Flag_CheckAlarm = RESET;


void Check_Alarm()
{
	u8 i;

	// beeper -> stm8s.pdf p122
	// BEEPEN
	if(SET == Flag_CheckAlarm)
	{
		Flag_CheckAlarm = RESET;
		ENBLE_BEEP();
		/*for(i=0;i<50;i++)
		 {
			PORT_BEEP =~ PORT_BEEP;
			//Delay(100);
		 }
		PORT_BEEP=1;*/
	}
}
