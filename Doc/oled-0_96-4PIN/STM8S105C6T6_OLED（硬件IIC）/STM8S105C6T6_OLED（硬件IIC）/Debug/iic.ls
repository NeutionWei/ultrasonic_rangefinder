   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.11.9 - 08 Feb 2017
   3                     ; Generator (Limited) V4.4.6 - 08 Feb 2017
2822                     ; 36 void IIC_Init(void)
2822                     ; 37 {
2824                     	switch	.text
2825  0000               _IIC_Init:
2829                     ; 38 	I2C_FREQR = 0x04;	//配置输入时钟为4M
2831  0000 35045212      	mov	_I2C_FREQR,#4
2832                     ; 40 	I2C_OARH = 0x40;	//地址模式 7位
2834  0004 35405214      	mov	_I2C_OARH,#64
2835                     ; 41 	I2C_OARL = 0x00;
2837  0008 725f5213      	clr	_I2C_OARL
2838                     ; 43 	I2C_ITR = 0x00;	//关闭所有中断
2840  000c 725f521a      	clr	_I2C_ITR
2841                     ; 45 	I2C_CCRH = 0x00;	//标准模式，SCL = 100kHz  tSCL = 10us  fCK = 4KhZ
2843  0010 725f521c      	clr	_I2C_CCRH
2844                     ; 46 	I2C_CCRL = 0x14;	//tSCL = tCL * CCR*3 = 0.25us * 20 *2 = 10us
2846  0014 3514521b      	mov	_I2C_CCRL,#20
2847                     ; 48 	I2C_TRISER = 0x02;	//最大上升时间（300ns标准模式） tCK = 250nS = tPCLK1  TRISE = 300/250 +1 = 2
2849  0018 3502521d      	mov	_I2C_TRISER,#2
2850                     ; 50 	I2C_CR2 |= 0x04;	//使能ACK应答，SWRST位清零
2852  001c 72145211      	bset	_I2C_CR2,#2
2853                     ; 51 	I2C_CR1 |= 0x01;	//使能IIC模块
2855  0020 72105210      	bset	_I2C_CR1,#0
2856                     ; 52 }
2859  0024 81            	ret
2915                     ; 61 void Wirte_Byte(unsigned char addr ,unsigned char data)
2915                     ; 62 {
2916                     	switch	.text
2917  0025               _Wirte_Byte:
2919  0025 89            	pushw	x
2920  0026 88            	push	a
2921       00000001      OFST:	set	1
2924  0027               L1302:
2925                     ; 65 	while(I2C_SR3 & 0x02); //检测总线空闲
2927  0027 c65219        	ld	a,_I2C_SR3
2928  002a a502          	bcp	a,#2
2929  002c 26f9          	jrne	L1302
2930                     ; 67 	I2C_CR2 |= 0x01;	//产生起始位
2932  002e 72105211      	bset	_I2C_CR2,#0
2934  0032               L7302:
2935                     ; 68 	while(!(I2C_SR1 & 0x01));	//检测发送是否完成，完成后SB位会为1
2937  0032 c65217        	ld	a,_I2C_SR1
2938  0035 a501          	bcp	a,#1
2939  0037 27f9          	jreq	L7302
2940                     ; 69 	I2C_DR = 0xa0;	//写器件地址，清零SB位
2942  0039 35a05216      	mov	_I2C_DR,#160
2944  003d               L7402:
2945                     ; 71 	while(!(I2C_SR1 & 0x02));	//ADDR位为1，则器件收到匹配地址
2947  003d c65217        	ld	a,_I2C_SR1
2948  0040 a502          	bcp	a,#2
2949  0042 27f9          	jreq	L7402
2950                     ; 72 	temp = I2C_SR1;	//先读SR1
2952  0044 c65217        	ld	a,_I2C_SR1
2953                     ; 73 	temp = I2C_SR3;	//再读SR3清除该标志
2955  0047 c65219        	ld	a,_I2C_SR3
2956                     ; 75 	I2C_DR = addr;	//写入器件存储器的地址
2958  004a 7b02          	ld	a,(OFST+1,sp)
2959  004c c75216        	ld	_I2C_DR,a
2961  004f               L7502:
2962                     ; 76 	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
2964  004f c65217        	ld	a,_I2C_SR1
2965  0052 a584          	bcp	a,#132
2966  0054 27f9          	jreq	L7502
2967                     ; 78 	I2C_DR = data;	//往器件的地址写入数据
2969  0056 7b03          	ld	a,(OFST+2,sp)
2970  0058 c75216        	ld	_I2C_DR,a
2972  005b               L7602:
2973                     ; 79 	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
2975  005b c65217        	ld	a,_I2C_SR1
2976  005e a584          	bcp	a,#132
2977  0060 27f9          	jreq	L7602
2978                     ; 81 	I2C_CR2 |= 0x02;	//产生停止位
2980  0062 72125211      	bset	_I2C_CR2,#1
2981                     ; 82 }
2984  0066 5b03          	addw	sp,#3
2985  0068 81            	ret
3041                     ; 90 unsigned char Read_Byte(unsigned char addr)
3041                     ; 91 {
3042                     	switch	.text
3043  0069               _Read_Byte:
3045  0069 88            	push	a
3046  006a 89            	pushw	x
3047       00000002      OFST:	set	2
3050  006b               L3212:
3051                     ; 94 	while(I2C_SR3 & 0x02);	//检测总线空闲
3053  006b c65219        	ld	a,_I2C_SR3
3054  006e a502          	bcp	a,#2
3055  0070 26f9          	jrne	L3212
3056                     ; 96 	I2C_CR2 |= 0x01;	//产生起始位
3058  0072 72105211      	bset	_I2C_CR2,#0
3060  0076               L1312:
3061                     ; 97 	while(!(I2C_SR1 & 0x01));	//检测发送是否完成，完成后SB位会为1
3063  0076 c65217        	ld	a,_I2C_SR1
3064  0079 a501          	bcp	a,#1
3065  007b 27f9          	jreq	L1312
3066                     ; 98 	I2C_DR = 0xa0;	//写器件地址，清零SB位
3068  007d 35a05216      	mov	_I2C_DR,#160
3070  0081               L1412:
3071                     ; 100 	while(!(I2C_SR1 & 0x02));	//ADDR位为1，则器件收到匹配地址
3073  0081 c65217        	ld	a,_I2C_SR1
3074  0084 a502          	bcp	a,#2
3075  0086 27f9          	jreq	L1412
3076                     ; 101 	temp = I2C_SR1;	//先读SR1
3078  0088 c65217        	ld	a,_I2C_SR1
3079                     ; 102 	temp = I2C_SR3;	//再读SR3清除该标志
3081  008b c65219        	ld	a,_I2C_SR3
3082                     ; 104 	I2C_DR = addr;	//写入器件存储器的地址
3084  008e 7b03          	ld	a,(OFST+1,sp)
3085  0090 c75216        	ld	_I2C_DR,a
3087  0093               L1512:
3088                     ; 105 	while(!(I2C_SR1 & 0x84));	//发送后检测TXE位是否为空，为空即数据发送完毕，检测BTF位是否发送结束
3090  0093 c65217        	ld	a,_I2C_SR1
3091  0096 a584          	bcp	a,#132
3092  0098 27f9          	jreq	L1512
3093                     ; 107 	I2C_CR2 |= 0x01;	//产生起始位
3095  009a 72105211      	bset	_I2C_CR2,#0
3097  009e               L7512:
3098                     ; 108 	while(!(I2C_SR1 & 0x01));	//检测发送是否完成，完成后SB位会为1
3100  009e c65217        	ld	a,_I2C_SR1
3101  00a1 a501          	bcp	a,#1
3102  00a3 27f9          	jreq	L7512
3103                     ; 110 	I2C_DR = 0xa1;	//器件地址加1，表示为读
3105  00a5 35a15216      	mov	_I2C_DR,#161
3107  00a9               L7612:
3108                     ; 111 	while(!(I2C_SR1 & 0x02));	//ADDR位为1，则器件收到匹配地址
3110  00a9 c65217        	ld	a,_I2C_SR1
3111  00ac a502          	bcp	a,#2
3112  00ae 27f9          	jreq	L7612
3113                     ; 112 	temp = I2C_SR1;	//先读SR1
3115  00b0 c65217        	ld	a,_I2C_SR1
3116                     ; 113 	temp = I2C_SR3;	//再读SR3清除该标志
3118  00b3 c65219        	ld	a,_I2C_SR3
3119                     ; 115 	I2C_CR2 |= 0x02;	//产生停止位
3121  00b6 72125211      	bset	_I2C_CR2,#1
3122                     ; 116 	I2C_CR2 &= 0xf3;	//不产生停止位，传送当前字节不应答
3124  00ba c65211        	ld	a,_I2C_CR2
3125  00bd a4f3          	and	a,#243
3126  00bf c75211        	ld	_I2C_CR2,a
3128  00c2               L5712:
3129                     ; 118 	while(!(I2C_SR1 & 0X40));	//等待接收数据完成
3131  00c2 c65217        	ld	a,_I2C_SR1
3132  00c5 a540          	bcp	a,#64
3133  00c7 27f9          	jreq	L5712
3134                     ; 119 	data = I2C_DR;	//读出数据，清RXNE位
3136  00c9 c65216        	ld	a,_I2C_DR
3137  00cc 6b01          	ld	(OFST-1,sp),a
3139                     ; 121 	I2C_CR2 |= 0x04;	//恢复产生应答信号
3141  00ce 72145211      	bset	_I2C_CR2,#2
3142                     ; 123 	return data;	//返回读取的值
3144  00d2 7b01          	ld	a,(OFST-1,sp)
3147  00d4 5b03          	addw	sp,#3
3148  00d6 81            	ret
3161                     	xdef	_Read_Byte
3162                     	xdef	_Wirte_Byte
3163                     	xdef	_IIC_Init
3182                     	end
