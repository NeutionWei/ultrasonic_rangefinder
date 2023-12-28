#ifndef	_DETECT_H
#define _DETECT_H

#include "typedef.h"
#include "iostm8s103f3.h"

//extern __IO FlagStatus Flag_DetectData;
extern __IO u16 DistanceData;
extern __IO u16 OutofDistance;
extern __IO FlagStatus Flag_dis_mistake ; // 距离数据出错标志
extern __IO FlagStatus Flag_dis_normal  ; // 距离数据正常标志
extern __IO FlagStatus Flag_dis_abnormal; // 距离数据过近标志

void Detect_Data();




#endif /* _DETECT_H */


