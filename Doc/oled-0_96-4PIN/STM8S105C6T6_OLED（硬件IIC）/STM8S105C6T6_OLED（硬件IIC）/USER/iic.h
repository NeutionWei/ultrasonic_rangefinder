#ifndef __IIC__H
#define __IIC__H


/*inclides-------------------------------------------------*/
#include "STM8S105C6.h"


/*declaration----------------------------------------------*/
void IIC_Init(void);//����IIC��ʼ������
void Wirte_Byte(unsigned char addr ,unsigned char data);//����д�ֽں���
unsigned char Read_Byte(unsigned char addr);//�������ֽں���


#endif

