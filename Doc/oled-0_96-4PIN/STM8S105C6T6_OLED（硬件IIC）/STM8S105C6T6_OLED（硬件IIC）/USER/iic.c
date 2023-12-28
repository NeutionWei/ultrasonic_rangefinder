/********************************************************
  * @file        	iic.c
  * @author      	LGG
  * @version     	V1.0.0
  * @data        	2017��6��9��
  * @brief        IIC�ļ�
  *
  *******************************************************
  *	@attention     �����ǰ��ն�ȡ24CXXΪ��
  *
	* I2C_CR1-���ƼĴ���1
	* I2C_CR2-���ƼĴ���2
	* I2C_FREQR-Ƶ�ʼĴ���
	* I2C_OARL-�����ַ�Ĵ���LSB
	* I2C_OARH-�����ַ�Ĵ���MSB
	* I2C_DR-���ݼĴ���
	* I2C_SR1-״̬�Ĵ���1
	* I2C_SR2-״̬�Ĵ���2
	* I2C_SR3-״̬�Ĵ���3
	* I2C_ITR-�жϼĴ���
	* I2C_CCRL-ʱ�ӿ��Ƶ�λ�Ĵ���
	* I2C_CCRH-ʱ�ӿ��Ƹ�λ�Ĵ���
	* I2C_TRISE-TRISE�Ĵ���---------ע�⣺д����Ĵ���ʱ��Ӧд I2C_TRISER
  *
********************************************************/


#include "iic.h"


/*
	@brief			��ʼ��IIC
	@param			��
	@retval			��
 */
void IIC_Init(void)
{
	I2C_FREQR = 0x04;	//��������ʱ��Ϊ4M
	
	I2C_OARH = 0x40;	//��ַģʽ 7λ
	I2C_OARL = 0x00;
	
	I2C_ITR = 0x00;	//�ر������ж�
	
	I2C_CCRH = 0x00;	//��׼ģʽ��SCL = 100kHz  tSCL = 10us  fCK = 4KhZ
	I2C_CCRL = 0x14;	//tSCL = tCL * CCR*3 = 0.25us * 20 *2 = 10us
	
	I2C_TRISER = 0x02;	//�������ʱ�䣨300ns��׼ģʽ�� tCK = 250nS = tPCLK1  TRISE = 300/250 +1 = 2
	
	I2C_CR2 |= 0x04;	//ʹ��ACKӦ��SWRSTλ����
	I2C_CR1 |= 0x01;	//ʹ��IICģ��
}


/*
	@brief			IICдһ���ֽ�
	@param			addr��д��ĵ�ַ
							data����������ָ����ַд������
	@retval			��
 */
void Wirte_Byte(unsigned char addr ,unsigned char data)
{
	unsigned char temp;	//�������
	
	while(I2C_SR3 & 0x02); //������߿���
	
	I2C_CR2 |= 0x01;	//������ʼλ
	while(!(I2C_SR1 & 0x01));	//��ⷢ���Ƿ���ɣ���ɺ�SBλ��Ϊ1
	I2C_DR = 0xa0;	//д������ַ������SBλ
	
	while(!(I2C_SR1 & 0x02));	//ADDRλΪ1���������յ�ƥ���ַ
	temp = I2C_SR1;	//�ȶ�SR1
	temp = I2C_SR3;	//�ٶ�SR3����ñ�־
	
	I2C_DR = addr;	//д�������洢���ĵ�ַ
	while(!(I2C_SR1 & 0x84));	//���ͺ���TXEλ�Ƿ�Ϊ�գ�Ϊ�ռ����ݷ�����ϣ����BTFλ�Ƿ��ͽ���
	
	I2C_DR = data;	//�������ĵ�ַд������
	while(!(I2C_SR1 & 0x84));	//���ͺ���TXEλ�Ƿ�Ϊ�գ�Ϊ�ռ����ݷ�����ϣ����BTFλ�Ƿ��ͽ���
	
	I2C_CR2 |= 0x02;	//����ֹͣλ
}


/*
	@brief			��������ĳ��λ�ö�һ���ֽ�
	@param			addr���������ĵ�ַ
	@retval			data�����ض���������
 */
unsigned char Read_Byte(unsigned char addr)
{
	unsigned char temp,data;	//�������
	
	while(I2C_SR3 & 0x02);	//������߿���
	
	I2C_CR2 |= 0x01;	//������ʼλ
	while(!(I2C_SR1 & 0x01));	//��ⷢ���Ƿ���ɣ���ɺ�SBλ��Ϊ1
	I2C_DR = 0xa0;	//д������ַ������SBλ
	
	while(!(I2C_SR1 & 0x02));	//ADDRλΪ1���������յ�ƥ���ַ
	temp = I2C_SR1;	//�ȶ�SR1
	temp = I2C_SR3;	//�ٶ�SR3����ñ�־
	
	I2C_DR = addr;	//д�������洢���ĵ�ַ
	while(!(I2C_SR1 & 0x84));	//���ͺ���TXEλ�Ƿ�Ϊ�գ�Ϊ�ռ����ݷ�����ϣ����BTFλ�Ƿ��ͽ���
	
	I2C_CR2 |= 0x01;	//������ʼλ
	while(!(I2C_SR1 & 0x01));	//��ⷢ���Ƿ���ɣ���ɺ�SBλ��Ϊ1
	
	I2C_DR = 0xa1;	//������ַ��1����ʾΪ��
	while(!(I2C_SR1 & 0x02));	//ADDRλΪ1���������յ�ƥ���ַ
	temp = I2C_SR1;	//�ȶ�SR1
	temp = I2C_SR3;	//�ٶ�SR3����ñ�־
	
	I2C_CR2 |= 0x02;	//����ֹͣλ
	I2C_CR2 &= 0xf3;	//������ֹͣλ�����͵�ǰ�ֽڲ�Ӧ��
	
	while(!(I2C_SR1 & 0X40));	//�ȴ������������
	data = I2C_DR;	//�������ݣ���RXNEλ
	
	I2C_CR2 |= 0x04;	//�ָ�����Ӧ���ź�
	
	return data;	//���ض�ȡ��ֵ
}








