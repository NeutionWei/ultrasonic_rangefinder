/********************************************************
  * @file        	oled.c
  * @author      	LGG
  * @version     	V1.0.0
  * @data        	2017年06月6号
  * @brief       	OELD文件
  *
  *******************************************************
  *	@attention
  *
  *	PG0-->LED1		PG1-->LED2
  * Px_ODR-输出数据寄存器
  * Px_IDR-输入数据寄存器
  * Px_DDR-数据方向寄存器
  * Px_CR1-控制寄存器1
  * Px_CR2-控制寄存器2
  *
********************************************************/


/*includes----------------------------------------------*/
#include "oled.h"
#include "oledfont.h"  	 
#include "iostm8s103f3.h"
#include "init.h"
//#include "led.h"
#include "iic.h"


/*definition--------------------------------------------*/




/*
	@brief			IIC写入命令
	@param			IIC_Command：写入的命令
	@retval			无
 */
void Write_IIC_Command(unsigned char IIC_Command)
{
	unsigned char temp;	//定义变量
	
	while(I2C_SR3 & 0x02); //检测总线空闲
	
	I2C_CR2 |= 0x01;	//产生起始位
	while(!(I2C_SR1 & 0x01));	//检测发送是否完成，完成后SB位会为1
	
	I2C_DR = 0x78;	//写器件地址，清零SB位
	
	while(!(I2C_SR1 & 0x02));	//ADDR位为1，则器件收到匹配地址
	temp = I2C_SR1;	//先读SR1
	temp = I2C_SR3;	//再读SR3清除该标志
	
	I2C_DR = 0x00;	//写入命令
	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
	
	I2C_DR = IIC_Command;	//往器件的地址写入数据
	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
	
	I2C_CR2 |= 0x02;	//产生停止位
}


/*
	@brief			IIC写入数据
	@param			IIC_Data：数据
	@retval			无
 */
void Write_IIC_Data(unsigned char IIC_Data)
{
	unsigned char temp;	//定义变量
	
	while(I2C_SR3 & 0x02); //检测总线空闲
	
	I2C_CR2 |= 0x01;	//产生起始位
	while(!(I2C_SR1 & 0x01));	//检测发送是否完成，完成后SB位会为1
	
	I2C_DR = 0x78;	//写器件地址，清零SB位
	
	while(!(I2C_SR1 & 0x02));	//ADDR位为1，则器件收到匹配地址
	temp = I2C_SR1;	//先读SR1
	temp = I2C_SR3;	//再读SR3清除该标志
	
	I2C_DR = 0x40;	//写入数据
	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
	
	I2C_DR = IIC_Data;	//往器件的地址写入数据
	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
	
	I2C_CR2 |= 0x02;	//产生停止位
}

/*
	@brief			对OLED写入一个字节
	@param			dat：数据
					cmd：1，写诶数据；0，写入命令
	@retval			无
 */
void OLED_WR_Byte(unsigned char dat,unsigned char cmd)
{
	if(cmd) 
	  {
       Write_IIC_Data(dat); //写入数据
	  }
	else {
       Write_IIC_Command(dat); //写入命令
	}
}


/*
	@brief			画点
	@param			x：列的起始低地址与起始高地址；0x00~0x0f：设置起始列低地址（在页寻址模式）；0x10~0x1f：设置起始列高地址（在页寻址模式）
					y：起始页地址 0~7
	@retval			无
 */
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);	//写入页地址
	OLED_WR_Byte((x&0x0f),OLED_CMD);	//写入列低地址
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);	//写入列高地址
}   	  


/*
	@brief			开显示
	@param			无
	@retval			无
 */ 
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //设置OLED电荷泵
	OLED_WR_Byte(0X14,OLED_CMD);  //使能，开
	OLED_WR_Byte(0XAF,OLED_CMD);  //开显示
}


/*
	@brief			关显示
	@param			无
	@retval			无
 */  
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //设置OLED电荷泵
	OLED_WR_Byte(0X10,OLED_CMD);  //失能，关
	OLED_WR_Byte(0XAE,OLED_CMD);  //关显示
}		   			 


/*
	@brief			清屏
	@param			无
	@retval			无
 */	  
void OLED_Clear(void)  
{  
	unsigned char i,n;		    //定义变量
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //从0~7页依次写入
		OLED_WR_Byte (0x00,OLED_CMD);      //列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //列高地址  
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); //写入 0 清屏
	}
}


/*
	@brief			显示一个字符
	@param			x：起始列
					y：起始页，SIZE = 16占两页；SIZE = 12占1页
					chr：字符
	@retval			无
 */
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' '; //获取字符的偏移量	
		if(x>Max_Column-1){x=0;y=y+2;} //如果列书超出了范围，就从下2页的第0列开始
		if(SIZE ==16) //字符大小如果为 16 = 8*16
			{
			OLED_Set_Pos(x,y);	//从x y 开始画点
			for(i=0;i<8;i++)  //循环8次 占8列
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA); //找出字符 c 的数组位置，先在第一页把列画完
			OLED_Set_Pos(x,y+1); //页数加1
			for(i=0;i<8;i++)  //循环8次
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA); //把第二页的列数画完
			}
			else {	//字符大小为 6 = 6*8
				OLED_Set_Pos(x,y+1); //一页就可以画完
				for(i=0;i<6;i++) //循环6次 ，占6列
				OLED_WR_Byte(F6x8[c][i],OLED_DATA); //把字符画完
			}
}


/*
	@brief			计算m^n
	@param			m：输入的一个数
					n：输入数的次方
	@retval			result：一个数的n次方
 */
unsigned int oled_pow(unsigned char m,unsigned char n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}				  


/*
	@brief			在指定的位置，显示一个指定长度大小的数
	@param			x：起始列
					y：起始页
					num：数字
					len：数字的长度
					size：数据的值
	@retval			无
 */		  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2)
{         	
	unsigned char t,temp;  //定义变量
	unsigned char enshow=0;		//定义变量
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;//取出输入数的每个位，由高到低
		if(enshow==0&&t<(len-1)) //enshow：是否为第一个数；t<(len-1)：判断是否为最后一个数
		{
			if(temp==0) //如果该数为0 
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ');//显示 0 ；x+(size2/2)*t根据字体大小偏移的列数（8）
				continue; //跳过剩下语句，继续重复循环（避免重复显示）
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0'); //显示一个位；x+(size2/2)*t根据字体大小偏移的列数（8）
	}
} 


/*
	@brief			显示字符串
	@param			x：起始列
					y：起始页
					*chr：第一个字符首地址
	@retval			无
 */
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
	unsigned char j=0; //定义变量
	while (chr[j]!='\0') //如果不是最后一个字符
	{		
		OLED_ShowChar(x,y,chr[j]); //显示字符
			x+=8; //列数加8 ，一个字符的列数占8
		if(x>120){x=0;y+=2;} //如果x超过128，切换页，从该页的第一列显示
			j++; //下一个字符
	}
}


/*
	@brief			显示中文
	@param			x：起始列；一个字体占16列
					y：起始页；一个字体占两页
					no：字体的序列号
	@retval			无

void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0; //定义变量
	OLED_Set_Pos(x,y);	//从 x y 开始画点，先画第一页
    for(t=0;t<16;t++) //循环16次，画第一页的16列
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);//画no在数组位置的第一页16列的点
     }	
		OLED_Set_Pos(x,y+1); //画第二列
    for(t=0;t<16;t++)	//循环16次，画第二页的16列
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);//画no在数组位置的第二页16列的点
      }					
}*/ 


/*
	@brief			显示图片
	@param			x0：起始列地址
					y0：起始页地址
					x1：终止列地址
					y1：终止页地址
					BMP[]：存放图片代码的数组
	@retval			无
 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0; //定义变量
 unsigned char x,y; //定义变量
  
  if(y1%8==0) y=y1/8;   //判断终止页是否为8的整数倍
  else y=y1/8+1;
	for(y=y0;y<y1;y++) //从起始页开始，画到终止页
	{
		OLED_Set_Pos(x0,y); //在页的起始列开始画
    for(x=x0;x<x1;x++) //画x1 - x0 列
	    {
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	//画图片的点    	
	    }
	}
} 


/*
	@brief			OLED初始化函数
	@param			无
	@retval			无
 */				    
void OLED_Init(void)
{

	IIC_Init();
 
    Delay(200);
	//delay_ms(200);	//延迟，由于单片机上电初始化比OLED快，所以必须加上延迟，等待OLED上电初始化完成

	OLED_WR_Byte(0xAE,OLED_CMD);	//关闭显示
	OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动

	OLED_WR_Byte(0x00,OLED_CMD);	//设置低列地址
	OLED_WR_Byte(0x10,OLED_CMD);	//设置高列地址
	OLED_WR_Byte(0x40,OLED_CMD);	//设置起始行地址
	OLED_WR_Byte(0xB0,OLED_CMD);	//设置页地址

	OLED_WR_Byte(0x81,OLED_CMD); 	// 对比度设置，可设置亮度
	OLED_WR_Byte(0xFF,OLED_CMD);	//  265  

	OLED_WR_Byte(0xA1,OLED_CMD);	//设置段（SEG）的起始映射地址；column的127地址是SEG0的地址
	OLED_WR_Byte(0xA6,OLED_CMD);	//正常显示；0xa7逆显示

	OLED_WR_Byte(0xA8,OLED_CMD);	//设置驱动路数
	OLED_WR_Byte(0x3F,OLED_CMD);	//1/32 duty
	
	OLED_WR_Byte(0xC8,OLED_CMD);	//重映射模式，COM[N-1]~COM0扫描

	OLED_WR_Byte(0xD3,OLED_CMD);	//设置显示偏移
	OLED_WR_Byte(0x00,OLED_CMD);	//无偏移
	
	OLED_WR_Byte(0xD5,OLED_CMD);	//设置震荡器分频（默认）大概370KHz
	OLED_WR_Byte(0x80,OLED_CMD);	
	
	OLED_WR_Byte(0xD8,OLED_CMD);	//设置 area color mode off（没有）
	OLED_WR_Byte(0x05,OLED_CMD);
	
	OLED_WR_Byte(0xD9,OLED_CMD);	//设置 Pre-Charge Period（默认）
	OLED_WR_Byte(0xF1,OLED_CMD);
	
	OLED_WR_Byte(0xDA,OLED_CMD);	//设置 com pin configuartion（默认）
	OLED_WR_Byte(0x12,OLED_CMD);
	
	OLED_WR_Byte(0xDB,OLED_CMD);	//设置 Vcomh，可调节亮度（默认）
	OLED_WR_Byte(0x30,OLED_CMD);
	
	OLED_WR_Byte(0x8D,OLED_CMD);	//设置OLED电荷泵
	OLED_WR_Byte(0x14,OLED_CMD);	//开显示

	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 

	OLED_WR_Byte(0xAF,OLED_CMD);//开启OLED面板显示
	OLED_Clear();        //清屏
	OLED_Set_Pos(0,0); 	 //画点
}  


/*
	@brief			OLED滚屏函数，范围0~1页，水平向左
	@param			无
	@retval			无
 */	
void OLED_Scroll(void)
{
	OLED_WR_Byte(0x2E,OLED_CMD);	//关闭滚动
	OLED_WR_Byte(0x27,OLED_CMD);	//水平向左滚动
	OLED_WR_Byte(0x00,OLED_CMD);	//虚拟字节
	OLED_WR_Byte(0x00,OLED_CMD);	//起始页 0
	OLED_WR_Byte(0x00,OLED_CMD);	//滚动时间间隔
	OLED_WR_Byte(0x01,OLED_CMD);	//终止页 1
	OLED_WR_Byte(0x00,OLED_CMD);	//虚拟字节
	OLED_WR_Byte(0xFF,OLED_CMD);	//虚拟字节
	OLED_WR_Byte(0x2F,OLED_CMD);	//开启滚动
}



