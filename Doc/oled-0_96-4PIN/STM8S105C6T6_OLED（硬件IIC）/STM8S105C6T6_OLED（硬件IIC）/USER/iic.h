#ifndef __IIC__H
#define __IIC__H


/*inclides-------------------------------------------------*/
#include "STM8S105C6.h"


/*declaration----------------------------------------------*/
void IIC_Init(void);//声明IIC初始化函数
void Wirte_Byte(unsigned char addr ,unsigned char data);//声明写字节函数
unsigned char Read_Byte(unsigned char addr);//声明读字节函数


#endif

