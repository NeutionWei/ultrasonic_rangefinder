#ifndef	_BEEP_H
#define _BEEP_H

#include "typedef.h"
#include "iostm8s103f3.h"


#define ON_BEEP()	(BEEP_CSR_BEEPEN=1)
#define OFF_BEEP()	(BEEP_CSR_BEEPEN=0)


extern __IO FlagStatus Flag_CheckAlarm;


void Check_Alarm();



#endif /* _BEEP_H */

