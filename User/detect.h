#ifndef	_DETECT_H
#define _DETECT_H

#include "typedef.h"
#include "iostm8s103f3.h"

#define MISTAKE_MAX  100
//#define NORMAL_MAX   2
//#define ABNORMAL_MAX 2
#define DETECT_MAX   60


enum{
  MISTAKE,
  NORMAL,
  ABNORMAL,
};


//extern __IO FlagStatus Flag_DetectData;
extern __IO u16 DistanceData;
extern __IO u16 OutofDistance;

extern __IO FlagStatus Flag_dis_mistake ; // 距离数据出错标志
extern __IO FlagStatus Flag_dis_normal  ; // 距离数据正常标志
extern __IO FlagStatus Flag_dis_abnormal; // 距离数据过近标志

extern __IO u8 curFlag_dis;
extern __IO u8 oldFlag_dis;
extern __IO u8 cnt_mistake,cnt_normal,cnt_abnormal;

void Detect_Data();




#endif /* _DETECT_H */


