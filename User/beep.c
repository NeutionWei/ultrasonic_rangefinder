#include "key.h"
#include "init.h"
#include "beep.h"
//#include "display.h"
#include "typedef.h"
#include "hc-sr04.h"
#include "iostm8s103f3.h"

__IO FlagStatus Flag_CheckAlarm = RESET;

void Init_Beep()
{
        LOW_TRIG();
	// Beeper初始化 -> stm8s.pdf p122
	// 00: fLS/(8 x BEEPDIV) kHz output
	// 01: fLS/(4 x BEEPDIV) kHz output
	// 1x: fLS/(2 x BEEPDIV) kHz output
	BEEP_CSR_BEEPDIV = 0x0E;	// 校验时钟 128k/16 = 8k
	BEEP_CSR_BEEPSEL = 2;		// 2k
}

void Check_Alarm()
{
	u8 i;

	// beeper -> stm8s.pdf p122
        // Note: This register must not be kept at its reset value (0x1F)
	// BEEPEN
	if(SET == Flag_CheckAlarm)
	{
		//Flag_CheckAlarm = RESET;
		ON_BEEP();
		/*for(i=0;i<50;i++)
		 {
			PORT_BEEP =~ PORT_BEEP;
			//Delay(100);
		 }
		PORT_BEEP=1;*/
	}
        else if(RESET == Flag_CheckAlarm)
        {
                OFF_BEEP();
        }
}
