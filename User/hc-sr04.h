#ifndef	_ULTRASONIC_H
#define _ULTRASONIC_H


/*__IO FlagStatus Flag_GetDistance   = RESET;
__IO FlagStatus Flag_DetectData    = RESET;

__IO FlagStatus Flag_DistDataNor   = RESET;		// Distance Data Normal
__IO FlagStatus Flag_DistDataUnNor = RESET;		// Distance Data Unnormal

__IO u16 DistanceData;
__IO u16 OutofDistance = 20;*/

                        
#define	LOW_TRIG()		(PORT_TRIG=0)
#define	HIGH_TRIG()		(PORT_TRIG=1)


#define	OutofDistance_Up	(400)
#define	OutofDistance_Down	(5)

// 每次计数0.5us, x_us/58 = x_cm <=> x_cnt*0.5/58 = x_cnt/116
#define ultra_formula(dis, cnt)  {dis=cnt/116;}

//__IO FlagStatus Flag_TRIG = RESET;
//__IO u32 Cnt_Level_ECHO = 0;
//__IO u32 Cnt_Level_TRIG = 0;


//void GetSignal();
//void SendSignal();
void Get_Distance();
void Detect_Data();

#endif /* _ULTRASONIC_H */
