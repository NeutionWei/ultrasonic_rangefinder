/********************************************************
  * @file        	oled.c
  * @author      	LGG
  * @version     	V1.0.0
  * @data        	2017��06��6��
  * @brief       	OELD�ļ�
  *
  *******************************************************
  *	@attention
  *
  *	PG0-->LED1		PG1-->LED2
  * Px_ODR-������ݼĴ���
  * Px_IDR-�������ݼĴ���
  * Px_DDR-���ݷ���Ĵ���
  * Px_CR1-���ƼĴ���1
  * Px_CR2-���ƼĴ���2
  *
********************************************************/


/*includes----------------------------------------------*/
#include "oled.h"
#include "oledfont.h"  	 
#include "stm8s105c6.h"
#include "led.h"
#include "iic.h"


/*definition--------------------------------------------*/




/*
	@brief			IICд������
	@param			IIC_Command��д�������
	@retval			��
 */
void Write_IIC_Command(unsigned char IIC_Command)
{
	unsigned char temp;	//�������
	
	while(I2C_SR3 & 0x02); //������߿���
	
	I2C_CR2 |= 0x01;	//������ʼλ
	while(!(I2C_SR1 & 0x01));	//��ⷢ���Ƿ���ɣ���ɺ�SBλ��Ϊ1
	
	I2C_DR = 0x78;	//д������ַ������SBλ
	
	while(!(I2C_SR1 & 0x02));	//ADDRλΪ1���������յ�ƥ���ַ
	temp = I2C_SR1;	//�ȶ�SR1
	temp = I2C_SR3;	//�ٶ�SR3����ñ�־
	
	I2C_DR = 0x00;	//д������
	while(!(I2C_SR1 & 0x84));	//���ͺ���TXEλ�Ƿ�Ϊ�գ�Ϊ�ռ����ݷ�����ϣ����BTFλ�Ƿ��ͽ���
	
	I2C_DR = IIC_Command;	//�������ĵ�ַд������
	while(!(I2C_SR1 & 0x84));	//���ͺ���TXEλ�Ƿ�Ϊ�գ�Ϊ�ռ����ݷ�����ϣ����BTFλ�Ƿ��ͽ���
	
	I2C_CR2 |= 0x02;	//����ֹͣλ
}


/*
	@brief			IICд������
	@param			IIC_Data������
	@retval			��
 */
void Write_IIC_Data(unsigned char IIC_Data)
{
	unsigned char temp;	//�������
	
	while(I2C_SR3 & 0x02); //������߿���
	
	I2C_CR2 |= 0x01;	//������ʼλ
	while(!(I2C_SR1 & 0x01));	//��ⷢ���Ƿ���ɣ���ɺ�SBλ��Ϊ1
	
	I2C_DR = 0x78;	//д������ַ������SBλ
	
	while(!(I2C_SR1 & 0x02));	//ADDRλΪ1���������յ�ƥ���ַ
	temp = I2C_SR1;	//�ȶ�SR1
	temp = I2C_SR3;	//�ٶ�SR3����ñ�־
	
	I2C_DR = 0x40;	//д������
	while(!(I2C_SR1 & 0x84));	//���ͺ���TXEλ�Ƿ�Ϊ�գ�Ϊ�ռ����ݷ�����ϣ����BTFλ�Ƿ��ͽ���
	
	I2C_DR = IIC_Data;	//�������ĵ�ַд������
	while(!(I2C_SR1 & 0x84));	//���ͺ���TXEλ�Ƿ�Ϊ�գ�Ϊ�ռ����ݷ�����ϣ����BTFλ�Ƿ��ͽ���
	
	I2C_CR2 |= 0x02;	//����ֹͣλ
}

/*
	@brief			��OLEDд��һ���ֽ�
	@param			dat������
					cmd��1��д�����ݣ�0��д������
	@retval			��
 */
void OLED_WR_Byte(unsigned char dat,unsigned char cmd)
{
	if(cmd) 
	  {
       Write_IIC_Data(dat); //д������
	  }
	else {
       Write_IIC_Command(dat); //д������
	}
}


/*
	@brief			����
	@param			x���е���ʼ�͵�ַ����ʼ�ߵ�ַ��0x00~0x0f��������ʼ�е͵�ַ����ҳѰַģʽ����0x10~0x1f��������ʼ�иߵ�ַ����ҳѰַģʽ��
					y����ʼҳ��ַ 0~7
	@retval			��
 */
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);	//д��ҳ��ַ
	OLED_WR_Byte((x&0x0f),OLED_CMD);	//д���е͵�ַ
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);	//д���иߵ�ַ
}   	  


/*
	@brief			����ʾ
	@param			��
	@retval			��
 */ 
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //����OLED��ɱ�
	OLED_WR_Byte(0X14,OLED_CMD);  //ʹ�ܣ���
	OLED_WR_Byte(0XAF,OLED_CMD);  //����ʾ
}


/*
	@brief			����ʾ
	@param			��
	@retval			��
 */  
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //����OLED��ɱ�
	OLED_WR_Byte(0X10,OLED_CMD);  //ʧ�ܣ���
	OLED_WR_Byte(0XAE,OLED_CMD);  //����ʾ
}		   			 


/*
	@brief			����
	@param			��
	@retval			��
 */	  
void OLED_Clear(void)  
{  
	unsigned char i,n;		    //�������
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //��0~7ҳ����д��
		OLED_WR_Byte (0x00,OLED_CMD);      //�е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //�иߵ�ַ  
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); //д�� 0 ����
	}
}


/*
	@brief			��ʾһ���ַ�
	@param			x����ʼ��
					y����ʼҳ��SIZE = 16ռ��ҳ��SIZE = 12ռ1ҳ
					chr���ַ�
	@retval			��
 */
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' '; //��ȡ�ַ���ƫ����	
		if(x>Max_Column-1){x=0;y=y+2;} //������鳬���˷�Χ���ʹ���2ҳ�ĵ�0�п�ʼ
		if(SIZE ==16) //�ַ���С���Ϊ 16 = 8*16
			{
			OLED_Set_Pos(x,y);	//��x y ��ʼ����
			for(i=0;i<8;i++)  //ѭ��8�� ռ8��
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA); //�ҳ��ַ� c ������λ�ã����ڵ�һҳ���л���
			OLED_Set_Pos(x,y+1); //ҳ����1
			for(i=0;i<8;i++)  //ѭ��8��
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA); //�ѵڶ�ҳ����������
			}
			else {	//�ַ���СΪ 6 = 6*8
				OLED_Set_Pos(x,y+1); //һҳ�Ϳ��Ի���
				for(i=0;i<6;i++) //ѭ��6�� ��ռ6��
				OLED_WR_Byte(F6x8[c][i],OLED_DATA); //���ַ�����
			}
}


/*
	@brief			����m^n
	@param			m�������һ����
					n���������Ĵη�
	@retval			result��һ������n�η�
 */
unsigned int oled_pow(unsigned char m,unsigned char n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}				  


/*
	@brief			��ָ����λ�ã���ʾһ��ָ�����ȴ�С����
	@param			x����ʼ��
					y����ʼҳ
					num������
					len�����ֵĳ���
					size�����ݵ�ֵ
	@retval			��
 */		  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2)
{         	
	unsigned char t,temp;  //�������
	unsigned char enshow=0;		//�������
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;//ȡ����������ÿ��λ���ɸߵ���
		if(enshow==0&&t<(len-1)) //enshow���Ƿ�Ϊ��һ������t<(len-1)���ж��Ƿ�Ϊ���һ����
		{
			if(temp==0) //�������Ϊ0 
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ');//��ʾ 0 ��x+(size2/2)*t���������Сƫ�Ƶ�������8��
				continue; //����ʣ����䣬�����ظ�ѭ���������ظ���ʾ��
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0'); //��ʾһ��λ��x+(size2/2)*t���������Сƫ�Ƶ�������8��
	}
} 


/*
	@brief			��ʾ�ַ���
	@param			x����ʼ��
					y����ʼҳ
					*chr����һ���ַ��׵�ַ
	@retval			��
 */
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
	unsigned char j=0; //�������
	while (chr[j]!='\0') //����������һ���ַ�
	{		
		OLED_ShowChar(x,y,chr[j]); //��ʾ�ַ�
			x+=8; //������8 ��һ���ַ�������ռ8
		if(x>120){x=0;y+=2;} //���x����128���л�ҳ���Ӹ�ҳ�ĵ�һ����ʾ
			j++; //��һ���ַ�
	}
}


/*
	@brief			��ʾ����
	@param			x����ʼ�У�һ������ռ16��
					y����ʼҳ��һ������ռ��ҳ
					no����������к�
	@retval			��
 */
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0; //�������
	OLED_Set_Pos(x,y);	//�� x y ��ʼ���㣬�Ȼ���һҳ
    for(t=0;t<16;t++) //ѭ��16�Σ�����һҳ��16��
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);//��no������λ�õĵ�һҳ16�еĵ�
     }	
		OLED_Set_Pos(x,y+1); //���ڶ���
    for(t=0;t<16;t++)	//ѭ��16�Σ����ڶ�ҳ��16��
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);//��no������λ�õĵڶ�ҳ16�еĵ�
      }					
}


/*
	@brief			��ʾͼƬ
	@param			x0����ʼ�е�ַ
					y0����ʼҳ��ַ
					x1����ֹ�е�ַ
					y1����ֹҳ��ַ
					BMP[]�����ͼƬ���������
	@retval			��
 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0; //�������
 unsigned char x,y; //�������
  
  if(y1%8==0) y=y1/8;   //�ж���ֹҳ�Ƿ�Ϊ8��������
  else y=y1/8+1;
	for(y=y0;y<y1;y++) //����ʼҳ��ʼ��������ֹҳ
	{
		OLED_Set_Pos(x0,y); //��ҳ����ʼ�п�ʼ��
    for(x=x0;x<x1;x++) //��x1 - x0 ��
	    {
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	//��ͼƬ�ĵ�    	
	    }
	}
} 


/*
	@brief			OLED��ʼ������
	@param			��
	@retval			��
 */				    
void OLED_Init(void)
{

	IIC_Init();
 
	delay_ms(200);	//�ӳ٣����ڵ�Ƭ���ϵ��ʼ����OLED�죬���Ա�������ӳ٣��ȴ�OLED�ϵ��ʼ�����

	OLED_WR_Byte(0xAE,OLED_CMD);	//�ر���ʾ
	OLED_WR_Byte(0x2e,OLED_CMD);	//�رչ���

	OLED_WR_Byte(0x00,OLED_CMD);	//���õ��е�ַ
	OLED_WR_Byte(0x10,OLED_CMD);	//���ø��е�ַ
	OLED_WR_Byte(0x40,OLED_CMD);	//������ʼ�е�ַ
	OLED_WR_Byte(0xB0,OLED_CMD);	//����ҳ��ַ

	OLED_WR_Byte(0x81,OLED_CMD); 	// �Աȶ����ã�����������
	OLED_WR_Byte(0xFF,OLED_CMD);	//  265  

	OLED_WR_Byte(0xA1,OLED_CMD);	//���öΣ�SEG������ʼӳ���ַ��column��127��ַ��SEG0�ĵ�ַ
	OLED_WR_Byte(0xA6,OLED_CMD);	//������ʾ��0xa7����ʾ

	OLED_WR_Byte(0xA8,OLED_CMD);	//��������·��
	OLED_WR_Byte(0x3F,OLED_CMD);	//1/32 duty
	
	OLED_WR_Byte(0xC8,OLED_CMD);	//��ӳ��ģʽ��COM[N-1]~COM0ɨ��

	OLED_WR_Byte(0xD3,OLED_CMD);	//������ʾƫ��
	OLED_WR_Byte(0x00,OLED_CMD);	//��ƫ��
	
	OLED_WR_Byte(0xD5,OLED_CMD);	//����������Ƶ��Ĭ�ϣ����370KHz
	OLED_WR_Byte(0x80,OLED_CMD);	
	
	OLED_WR_Byte(0xD8,OLED_CMD);	//���� area color mode off��û�У�
	OLED_WR_Byte(0x05,OLED_CMD);
	
	OLED_WR_Byte(0xD9,OLED_CMD);	//���� Pre-Charge Period��Ĭ�ϣ�
	OLED_WR_Byte(0xF1,OLED_CMD);
	
	OLED_WR_Byte(0xDA,OLED_CMD);	//���� com pin configuartion��Ĭ�ϣ�
	OLED_WR_Byte(0x12,OLED_CMD);
	
	OLED_WR_Byte(0xDB,OLED_CMD);	//���� Vcomh���ɵ������ȣ�Ĭ�ϣ�
	OLED_WR_Byte(0x30,OLED_CMD);
	
	OLED_WR_Byte(0x8D,OLED_CMD);	//����OLED��ɱ�
	OLED_WR_Byte(0x14,OLED_CMD);	//����ʾ

	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 

	OLED_WR_Byte(0xAF,OLED_CMD);//����OLED�����ʾ
	OLED_Clear();        //����
	OLED_Set_Pos(0,0); 	 //����
}  


/*
	@brief			OLED������������Χ0~1ҳ��ˮƽ����
	@param			��
	@retval			��
 */	
void OLED_Scroll(void)
{
	OLED_WR_Byte(0x2E,OLED_CMD);	//�رչ���
	OLED_WR_Byte(0x27,OLED_CMD);	//ˮƽ�������
	OLED_WR_Byte(0x00,OLED_CMD);	//�����ֽ�
	OLED_WR_Byte(0x00,OLED_CMD);	//��ʼҳ 0
	OLED_WR_Byte(0x00,OLED_CMD);	//����ʱ����
	OLED_WR_Byte(0x01,OLED_CMD);	//��ֹҳ 1
	OLED_WR_Byte(0x00,OLED_CMD);	//�����ֽ�
	OLED_WR_Byte(0xFF,OLED_CMD);	//�����ֽ�
	OLED_WR_Byte(0x2F,OLED_CMD);	//��������
}



