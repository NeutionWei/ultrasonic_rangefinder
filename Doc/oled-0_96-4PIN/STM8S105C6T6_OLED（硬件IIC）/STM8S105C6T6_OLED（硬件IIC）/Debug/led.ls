   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.11.9 - 08 Feb 2017
   3                     ; Generator (Limited) V4.4.6 - 08 Feb 2017
2816                     ; 34 void LED_Init(void)
2816                     ; 35 {
2818                     	switch	.text
2819  0000               _LED_Init:
2823                     ; 36 	PG_DDR |= 0x03;//将 PG0 PG1 口设为输出
2825  0000 c65020        	ld	a,_PG_DDR
2826  0003 aa03          	or	a,#3
2827  0005 c75020        	ld	_PG_DDR,a
2828                     ; 37 	PG_CR1 |= 0x03;//将 PG0 PG1 口设为推挽
2830  0008 c65021        	ld	a,_PG_CR1
2831  000b aa03          	or	a,#3
2832  000d c75021        	ld	_PG_CR1,a
2833                     ; 38 	PG_CR2 &= 0xfc;//将 PG0 PG1 口设为推挽
2835  0010 c65022        	ld	a,_PG_CR2
2836  0013 a4fc          	and	a,#252
2837  0015 c75022        	ld	_PG_CR2,a
2838                     ; 39 }
2841  0018 81            	ret
2893                     ; 48 void delay_ms(unsigned int ms)//延迟函数，MS级别
2893                     ; 49 {
2894                     	switch	.text
2895  0019               _delay_ms:
2897  0019 5204          	subw	sp,#4
2898       00000004      OFST:	set	4
2901                     ; 51 	for(x = ms;x>0;x--)
2903  001b 1f01          	ldw	(OFST-3,sp),x
2906  001d 2017          	jra	L3302
2907  001f               L7202:
2908                     ; 53 		for(y = 1300;y>0;y--);
2910  001f ae0514        	ldw	x,#1300
2911  0022 1f03          	ldw	(OFST-1,sp),x
2913  0024               L7302:
2917  0024 1e03          	ldw	x,(OFST-1,sp)
2918  0026 1d0001        	subw	x,#1
2919  0029 1f03          	ldw	(OFST-1,sp),x
2923  002b 1e03          	ldw	x,(OFST-1,sp)
2924  002d 26f5          	jrne	L7302
2925                     ; 51 	for(x = ms;x>0;x--)
2927  002f 1e01          	ldw	x,(OFST-3,sp)
2928  0031 1d0001        	subw	x,#1
2929  0034 1f01          	ldw	(OFST-3,sp),x
2931  0036               L3302:
2934  0036 1e01          	ldw	x,(OFST-3,sp)
2935  0038 26e5          	jrne	L7202
2936                     ; 55 }
2939  003a 5b04          	addw	sp,#4
2940  003c 81            	ret
2974                     ; 62 void delay_us(unsigned int us)
2974                     ; 63 {
2975                     	switch	.text
2976  003d               _delay_us:
2978  003d 89            	pushw	x
2979       00000000      OFST:	set	0
2982  003e               L5602:
2983                     ; 64 	while(us--);
2985  003e 1e01          	ldw	x,(OFST+1,sp)
2986  0040 1d0001        	subw	x,#1
2987  0043 1f01          	ldw	(OFST+1,sp),x
2988  0045 1c0001        	addw	x,#1
2989  0048 a30000        	cpw	x,#0
2990  004b 26f1          	jrne	L5602
2991                     ; 65 }
2994  004d 85            	popw	x
2995  004e 81            	ret
3008                     	xdef	_LED_Init
3009                     	xdef	_delay_us
3010                     	xdef	_delay_ms
3029                     	end
