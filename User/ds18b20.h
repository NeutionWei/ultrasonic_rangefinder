#ifndef	_DS18B20_H
#define _DS18B20_H

#include "typedef.h"
#include "iostm8s103f3.h"


/* 使用PA3作用ds18b20的DATA引脚 
#define DS18B20_DDR      PA_DDR_DDR3     // DS18B20 GPIO data direction register
#define DS18B20_ODR      PA_ODR_ODR3     // DS18B20 GPIO output data register
#define DS18B20_IDR      PA_IDR_IDR3     // DS18B20 GPIO pin input register
#define DS18B20_CR1      PA_CR1_C13      // DS18B20 GPIO control register 1
#define DS18B20_CR2      PA_CR2_C23*/

/* 使用PA3作用ds18b20的DATA引脚 */
#define DQ PA_ODR_ODR3
#define DI PA_IDR_IDR3

#define DQ_IN()  {PA_DDR_DDR3=0; PA_CR1_C13=1; PA_CR2_C23=0;}
#define DQ_OUT() {PA_DDR_DDR3=1; PA_CR1_C13=1; PA_CR2_C23=0;}

/* rom commands */
#define SEARCH_ROM           0xF0
#define READ_ROM             0x33
#define MATCH_ROM            0x55
#define SKIP_ROM             0xCC
#define ALARM_ROM            0xEC

/* functions commands */
#define CONVERT_TEAMPERATURE 0x44
#define WRITE_SCRATCHPAD     0x4E
#define READ_SCRATCHPAD      0xBE
#define COPY_SCRATCHPAD      0x48
#define RECALL_EEPROM        0xB8
#define READ_POWER_SUPPLY    0xB4

extern volatile unsigned int temp;
extern volatile unsigned int temp_buf;
extern volatile unsigned int tmp;
//unsigned int i =0;
extern volatile char sig;


void Get_Temperature();

#endif