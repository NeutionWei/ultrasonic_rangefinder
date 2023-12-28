#ifndef	_BEEP_H
#define _BEEP_H

#include "typedef.h"
#include "iostm8s103f3.h"


#define ENBLE_BEEP()	(BEEP_CSR_BEEPEN=1)

void Check_Alarm();



#endif /* _BEEP_H */

