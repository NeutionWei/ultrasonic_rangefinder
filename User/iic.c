/********************************************************
  * @file        	iic.c
  * @author      	LGG
  * @version     	V1.0.0
  * @data        	2017年6月9日
  * @brief        IIC文件
  *
  *******************************************************
  *	@attention     这里是按照读取24CXX为例
  *
	* I2C_CR1-控制寄存器1
	* I2C_CR2-控制寄存器2
	* I2C_FREQR-频率寄存器
	* I2C_OARL-自身地址寄存器LSB
	* I2C_OARH-自身地址寄存器MSB
	* I2C_DR-数据寄存器
	* I2C_SR1-状态寄存器1
	* I2C_SR2-状态寄存器2
	* I2C_SR3-状态寄存器3
	* I2C_ITR-中断寄存器
	* I2C_CCRL-时钟控制低位寄存器
	* I2C_CCRH-时钟控制高位寄存器
	* I2C_TRISE-TRISE寄存器---------注意：写这个寄存器时，应写 I2C_TRISER
  *
********************************************************/


#include "iic.h"


/*
	@brief			初始化IIC
	@param			无
	@retval			无
 */
void IIC_Init(void)
{
	I2C_FREQR = 0x04;	//配置输入时钟为4M
	
	I2C_OARH = 0x40;	//地址模式 7位
	I2C_OARL = 0x00;
	
	I2C_ITR = 0x00;	//关闭所有中断
	
	I2C_CCRH = 0x00;	//标准模式，SCL = 100kHz  tSCL = 10us  fCK = 4KhZ
	I2C_CCRL = 0x14;	//tSCL = tCL * CCR*3 = 0.25us * 20 *2 = 10us
	
	I2C_TRISER = 0x02;	//最大上升时间（300ns标准模式） tCK = 250nS = tPCLK1  TRISE = 300/250 +1 = 2
	
	I2C_CR2 |= 0x04;	//使能ACK应答，SWRST位清零
	I2C_CR1 |= 0x01;	//使能IIC模块
}


/*
	@brief			IIC写一个字节
	@param			addr：写入的地址
							data：在器件的指定地址写入数据
	@retval			无
 */
void Wirte_Byte(unsigned char addr ,unsigned char data)
{
	unsigned char temp;	//定义变量
	
	while(I2C_SR3 & 0x02); //检测总线空闲
	
	I2C_CR2 |= 0x01;	//产生起始位
	while(!(I2C_SR1 & 0x01));	//检测发送是否完成，完成后SB位会为1
	I2C_DR = 0xa0;	//写器件地址，清零SB位
	
	while(!(I2C_SR1 & 0x02));	//ADDR位为1，则器件收到匹配地址
	temp = I2C_SR1;	//先读SR1
	temp = I2C_SR3;	//再读SR3清除该标志
	
	I2C_DR = addr;	//写入器件存储器的地址
	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
	
	I2C_DR = data;	//往器件的地址写入数据
	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
	
	I2C_CR2 |= 0x02;	//产生停止位
}


/*
	@brief			在器件的某个位置读一个字节
	@param			addr：该器件的地址
	@retval			data：返回读到的数据
 */
unsigned char Read_Byte(unsigned char addr)
{
	unsigned char temp,data;	//定义变量
	
	while(I2C_SR3 & 0x02);	//检测总线空闲
	
	I2C_CR2 |= 0x01;	//产生起始位
	while(!(I2C_SR1 & 0x01));	//检测发送是否完成，完成后SB位会为1
	I2C_DR = 0xa0;	//写器件地址，清零SB位
	
	while(!(I2C_SR1 & 0x02));	//ADDR位为1，则器件收到匹配地址
	temp = I2C_SR1;	//先读SR1
	temp = I2C_SR3;	//再读SR3清除该标志
	
	I2C_DR = addr;	//写入器件存储器的地址
	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
	
	I2C_CR2 |= 0x01;	//产生起始位
	while(!(I2C_SR1 & 0x01));	//检测发送是否完成，完成后SB位会为1
	
	I2C_DR = 0xa1;	//器件地址加1，表示为读
	while(!(I2C_SR1 & 0x02));	//ADDR位为1，则器件收到匹配地址
	temp = I2C_SR1;	//先读SR1
	temp = I2C_SR3;	//再读SR3清除该标志
	
	I2C_CR2 |= 0x02;	//产生停止位
	I2C_CR2 &= 0xf3;	//不产生停止位，传送当前字节不应答
	
	while(!(I2C_SR1 & 0X40));	//等待接收数据完成
	data = I2C_DR;	//读出数据，清RXNE位
	
	I2C_CR2 |= 0x04;	//恢复产生应答信号
	
	return data;	//返回读取的值
}








