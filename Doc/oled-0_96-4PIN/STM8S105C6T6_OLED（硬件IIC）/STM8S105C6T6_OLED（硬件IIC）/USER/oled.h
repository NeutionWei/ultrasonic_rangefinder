#ifndef __OLED__H
#define __OLED__H			  	 


/*definition--------------------------------------------*/
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0

#define SIZE 16
#define Max_Column	128
#define Max_Row		64 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  				   


/*declaration----------------------------------------------*/
void OLED_WR_Byte(unsigned char dat,unsigned char cmd);	  //声明OLED写字节函数
void OLED_Display_On(void);	//声明 开显示 函数
void OLED_Display_Off(void);//声明 关显示 函数
void OLED_Init(void);	//声明 OLED初始化 函数
void OLED_Clear(void);  //声明 清屏 函数
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr); //声明 显示字符 函数
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2); //声明 在指定的位置，显示一个指定长度大小的数 函数
void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p);	 //声明 在指定位置开始显示字符串 函数
void OLED_Set_Pos(unsigned char x, unsigned char y);		//声明 画点 函数
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no); //声明 在指定位置显示汉字 函数
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]); //声明 显示图片 函数
void OLED_Scroll(void);

#endif  
	 



