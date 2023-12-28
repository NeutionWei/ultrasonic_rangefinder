#include "iostm8s103f3.h"
#include "typedef.h"
#include "key.h"
#include "init.h"
#include "beep.h"
#include "hc-sr04.h"
#include "display.h"
#include "oled.h"
#include "ds18b20.h"


//#define OUT_DQ()        {PA_DDR |= (1<<3);PA_CR1 |= (1<<3);}
//#define IN_DQ()         {PA_DDR &= ~(1<<3);PA_CR1 &= ~(1<<3);}
//#define SET_DQ()        {PA_ODR |= (1<<3);}
//#define CLR_DQ()        {PA_ODR &= ~(1<<3);}
//#define GET_DQ()        {PA_IDR & (1<<3);}
/*
void OUT_DQ()
{
        PA_DDR |= (1<<3);
        PA_CR1 |= (1<<3);
}

void IN_DQ()
{
        PA_DDR &= ~(1<<3);
        PA_CR1 &= ~(1<<3);
}

void SET_DQ()
{
        PA_ODR |= (1<<3);
}

void CLR_DQ()
{
        PA_ODR &= ~(1<<3);
}

u8 GET_DQ()        
{
        return ();
}

//-----复位-----
void resetOnewire(void) 
{
        OUT_DQ();
        CLR_DQ();
        usdelay_TIM4(500);
        //_delay_us(750);
        SET_DQ();
        usdelay_TIM4(100);
        //_delay_us(100);
        IN_DQ(); 
        //while(GET_DQ());
        while(!(GET_DQ()));
        OUT_DQ();
        SET_DQ();
}

//-----读数据-----
u8 rOnewire(void)
{
        u8 data=0,i=0;
        
        for(i=0; i<8; i++)
        {
                data = data>>1;
                OUT_DQ();
                CLR_DQ();
                usdelay_TIM4(2);
                IN_DQ();
                usdelay_TIM4(2);
                if(GET_DQ()) data |= 0x80;
                //else while(!(GET_DQ()));
                usdelay_TIM4(56);
                //_delay_us(60);
        }
        return(data);
}
//-----写数据-----
void wOnewire(u8 data)
{
        u8 i=0;
        
        OUT_DQ();
        for(i=0;i<8;i++)
        {
                CLR_DQ();
                if(data & 0x01)
                {
                    usdelay_TIM4(2);
                    SET_DQ();
                    usdelay_TIM4(58);
                }
                else
                {
                    //CLR_DQ();
                    usdelay_TIM4(60);
                }
                data = data>>1;
                SET_DQ();
                //_delay_us(60);  //65
                usdelay_TIM4(2);
        }
}

//-----ds18b2018B20转换温度-----
void convertDs18b20(void) 
{ 
        resetOnewire(); 
        wOnewire(0xcc); 
        wOnewire(0x44); 
}
//------------ds18b2018BB0读温度----------
u8 readTemp(void) 
{ 
        u8 temp1,temp2;
        
        convertDs18b20();
        resetOnewire(); 
        wOnewire(0xcc); 
        wOnewire(0xbe);         
        temp1  = rOnewire(); 
        temp2  = rOnewire(); 
        temp2  = temp2<<4;
        temp1  = temp1>>4;
        temp2 |= temp1;
        return (temp2 & 0x7F);
}*/


/*
#define ds18b2018B20_DQ_OUT          PA_DDR_DDR3 = 1   //输出
#define ds18b2018B20_DQ_IN           PA_DDR_DDR3 = 0   //输入
#define ds18b2018B20_DQ_HIGH         PA_ODR_ODR3 = 1   //拉高
#define ds18b2018B20_DQ_LOW          PA_ODR_ODR3 = 0   //拉低
#define ds18b2018B20_DQ_PULL_UP      PA_CR1_C13  = 1   //上拉
#define ds18b2018B20_DQ_FLOATING     PA_CR1_C13  = 0   //浮空
#define ds18b2018B20_DQ_PUSH_PULL    PA_CR1_C13  = 1   //推挽
#define ds18b2018B20_DQ_OPEN_DRAIN   PA_CR1_C13  = 0   //开漏
#define ds18b2018B20_DQ_VALUE        PA_IDR_IDR3       //DQ值



void _delay_us(unsigned int i)
{
    i *= 3; 
    while(--i);
}

void _delay_ms(unsigned int i)
{
    while(i--)
    {
        _delay_us(1000);
    }
}

void ds18b2018B20_Init(void)
{
    ds18b2018B20_DQ_OUT;   
    ds18b2018B20_DQ_PUSH_PULL;    
    ds18b2018B20_DQ_HIGH;   
    _delay_us(10);
    ds18b2018B20_DQ_LOW;   
    _delay_us(600);     //复位脉冲
    
    ds18b2018B20_DQ_IN;   
    ds18b2018B20_DQ_PULL_UP;    
    _delay_us(100);     
    while(ds18b2018B20_DQ_VALUE == 1);
    _delay_us(400);
}

void ds18b2018B20_writeriteByte(unsigned char _data)
{
    unsigned char i = 0;

    ds18b2018B20_DQ_OUT;
    for (i = 0; i < 8; i++)
    {
        ds18b2018B20_DQ_LOW;
        _delay_us(2);
        if (_data & 0x01)
        {
            ds18b2018B20_DQ_HIGH;
        }
        _data >>= 1;
        _delay_us(60);
        ds18b2018B20_DQ_HIGH;
    }
}

unsigned char ds18b2018B20_ReadByte(void)
{
    unsigned char i = 0, _data = 0;

    for (i = 0; i < 8; i++)
    {
        ds18b2018B20_DQ_OUT;
        ds18b2018B20_DQ_LOW;
        _delay_us(5);
        _data >>= 1;
        ds18b2018B20_DQ_HIGH;
        ds18b2018B20_DQ_IN;
        if (ds18b2018B20_DQ_VALUE)
        {
            _data |= 0x80;
        }
        ds18b2018B20_DQ_OUT; 
        ds18b2018B20_DQ_HIGH;
        _delay_us(60);
    }

    return _data;
}

float ds18b2018B20_ReadTemperature(void)
{
    unsigned char temp = 0;
    float t = 0;
    
    ds18b2018B20_Init();ON_LED_G();
    ds18b2018B20_writeriteByte(0xcc);
    ds18b2018B20_writeriteByte(0x44);
    
    ds18b2018B20_Init();
    ds18b2018B20_writeriteByte(0xcc);
    ds18b2018B20_writeriteByte(0xbe);

    temp = ds18b2018B20_ReadByte();
    OLED_ShowNum(45, 4, temp, 3, 16);
    t = (((temp & 0xf0) >> 4) + (temp & 0x07) * 0.125); 
    temp = ds18b2018B20_ReadByte();
    OLED_ShowNum(45, 4, temp, 3, 16);
    t += ((temp & 0x0f) << 4);
    
    return t;
}*/



volatile unsigned int temp_buf = 0;
volatile unsigned int temp = 0;
volatile unsigned int tmp;
//unsigned int i =0;
volatile char sig=0;


char ds18b20_reset() //复位
{
  char flag = 0;
  char i = 4;
  
  DQ_OUT();       //输出模式
  
  DQ = 0;         //拉低总线
  usdelay_TIM4(500); //延时500us
  DQ = 1;         //拉高总线
  
  DQ_IN();        //输入模式
  usdelay_TIM4(20);  //等待20us
  
  while(i--)
  {
    if(DI == 0) flag = 1; //有应答
    usdelay_TIM4(100);
  }
  
  return flag;  //应答反馈 
}

void ds18b20_write(char dat) //写数据
{
  char i;
  
  DQ_OUT();               //输出模式
  for(i=0; i<8; i++)
  {
    DQ = 0;               //拉低总线，启动传输
    usdelay_TIM4(2);         //延时2us
    if(dat & 0x01) DQ = 1;  //发1则拉高总线
    dat >>= 1;            //下一位数据
    usdelay_TIM4(58);        //延时58us
    DQ = 1;               //拉高总线
    usdelay_TIM4(2);         //延时2us
  }
}

unsigned char ds18b20_read()             //读数据
{
  char i;
  unsigned char dat = 0;
  //ON_LED_Y();
  for(i=0; i<8; i++)      
  {
    DQ_OUT();             //输出模式
    //ON_LED_Y();
    DQ = 0;               //拉低总线
    usdelay_TIM4(2);         //延时2us
    DQ = 1;               //拉高总线
    //ON_LED_Y();
    DQ_IN();              //输入模式
    //usdelay_TIM4(5);         //延时2us
    //ON_LED_Y();
    usdelay_TIM4(2);         //等待2us
    //ON_LED_Y();
    dat >>= 1;            //移位
    if(DI) dat |= 0x80;   //读取数据
    usdelay_TIM4(55);        //延时55us
  }
  //ON_LED_Y();
  return dat;           //返回数值
}

// CRC8校验程序
unsigned char calcrc_1byte(unsigned abyte)
{
  unsigned char i;
  unsigned char crc_1byte = 0;
  
  for(i=0; i<8; i++)
  {
    if((crc_1byte^abyte) & 0x01)
    {
      crc_1byte ^= 0x18;
      crc_1byte >>= 1;
      crc_1byte |= 0x80;
    }
    else
    {
      crc_1byte >>= 1;
      abyte >>= 1;
    }
  }
  return crc_1byte;
}

unsigned char calcrc_bytes(unsigned char *p, unsigned char len)
{
  unsigned char crc = 0;
  
  while(len--)  // len为总共要检验的字节数
  {
    crc = calcrc_1byte(crc ^ *p++);
  }
  return crc;   // 若最终返回的crc为0，则数据传输成功
}

// 平均值计算
int ave_process()
{
	static volatile int   adc_exist;
	volatile unsigned int adc_data;
	static volatile unsigned int  adc_max = 0;
	static volatile unsigned int  adc_min = 0;
	static volatile unsigned int  adc_sum = 0;
	static volatile unsigned char adc_cnt = 0;
        static volatile unsigned int  adc_ave = 0;

	if(0 != temp)
	{
		
		adc_data  = temp;
		
		
		/* 找出最大最小值 */
		if(!adc_exist)
		{
			adc_exist = 1;
			adc_max = adc_data;
			adc_min = adc_data;
		}
		else if(adc_data > adc_max)
			adc_max = adc_data;
		else if(adc_data < adc_min)
			adc_min = adc_data;
			
		adc_sum +=  adc_data;
		if(++adc_cnt >= 6)
		{
			adc_sum -= adc_max;
			adc_sum -= adc_min;
			
                        adc_ave = (adc_sum >> 2);
			
                        /*ultra_formula(DistanceData, adc_ave);
                        Dis[0] = DistanceData/100;
                        Dis[1] = DistanceData%100/10;
                        Dis[2] = DistanceData%10;
                        OLED_ShowNum(15, 6, Dis[0], 1, 16);
                        OLED_ShowNum(25, 6, Dis[1], 1, 16);
                        OLED_ShowNum(35, 6, Dis[2], 1, 16);*/
                        
			if(adc_max <= (adc_min+10))
                        {
                                
                                temp_buf = adc_ave;
                                
                                adc_sum = 0;
                                adc_max = 0;
                                adc_min = 0;
                                adc_cnt = 0;
                                adc_exist = 0;
                                return 0;
                                /*Dis[0] = DistanceData/100;
                                Dis[1] = DistanceData%100/10;
                                Dis[2] = DistanceData%10;
                                OLED_ShowNum(15, 6, Dis[0], 1, 16);
                                OLED_ShowNum(25, 6, Dis[1], 1, 16);
                                OLED_ShowNum(35, 6, Dis[2], 1, 16);*/
				//Flag_ADC_Success = SET;
			}
			adc_sum = 0;
                        adc_max = 0;
                        adc_min = 0;
                        adc_cnt = 0;
                        adc_exist = 0;	
			
                        return -1;
		}
	}
	else
	{
		adc_sum = 0;
		adc_min = 0;
		adc_max = 0;
		adc_cnt = 0;
//		adc_exist = 0;
                return -1;
	}
        return -1;
}


void Get_Temperature()
{
    //int i;
    //unsigned char data_byte[9];
  
    ds18b20_reset();         //复位
    //ON_LED_Y();
    ds18b20_write(SKIP_ROM);         //跳过rom
    //ON_LED_Y();
    ds18b20_write(CONVERT_TEAMPERATURE);         //温度转换指令
    //ON_LED_Y();
    usdelay_TIM4(750);       //等待转换完成750ms
    //ON_LED_Y();
    ds18b20_reset();         //复位
    ds18b20_write(SKIP_ROM);         //跳过rom
    ds18b20_write(READ_SCRATCHPAD);         //读取暂存器
    //ON_LED_Y();
    
    /*for(i=0; i<9; i++)
      data_byte[i] = ds18b20_read();
    
    if(0 == calcrc_bytes(data_byte, 9))
    {
      tmp  = data_byte[0];
      temp = data_byte[1];
    }
    else
    {
      //tmp  = 0;
      //temp = 0;
    }*/
    tmp  = ds18b20_read();
    temp = ds18b20_read();
    //ON_LED_Y();
    temp <<= 8;
    temp |= tmp;
    
    /*if(temp&0xf000)
    {
      temp=~temp+1; //取补码
      sig=1;
    }else
    {
      sig=0;
    }*/
  
    tmp = temp & 0x0f;
    temp >>= 4;
    temp &= 0x007f; 
    tmp *= 625;
    ave_process();
    /*if(temp > 50 || temp < 10)  // 临时调试
    {
      temp = 0;
    }*/
      //return;
    //Delay(100);
    //OLED_ShowNum(30, 4, temp/256, 2, 16);
    //OLED_ShowNum(30, 6, temp%256, 2, 16);  
}

