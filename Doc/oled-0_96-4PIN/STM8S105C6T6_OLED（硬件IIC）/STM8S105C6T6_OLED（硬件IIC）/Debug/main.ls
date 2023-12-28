   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.11.9 - 08 Feb 2017
   3                     ; Generator (Limited) V4.4.6 - 08 Feb 2017
2821                     ; 49 main()
2821                     ; 50 {
2823                     	switch	.text
2824  0000               _main:
2828                     ; 51 	CLK_CKDIVR = 0x00;//f_HSI = f_HSI RC 输出    f_CPU = f_MASTER    16M
2830  0000 725f50c6      	clr	_CLK_CKDIVR
2831                     ; 53 	LED_Init();	//LED初始化
2833  0004 cd0000        	call	_LED_Init
2835                     ; 55 	OLED_Init();	//OLED初始化
2837  0007 cd0000        	call	_OLED_Init
2839                     ; 56 	OLED_Clear();	//OLED清屏
2841  000a cd0000        	call	_OLED_Clear
2843                     ; 58 	OLED_ShowString(30,2,"OLED TEST");//OLED显示  OLED TEST
2845  000d ae0000        	ldw	x,#L1002
2846  0010 89            	pushw	x
2847  0011 ae1e02        	ldw	x,#7682
2848  0014 cd0000        	call	_OLED_ShowString
2850  0017 85            	popw	x
2851                     ; 60 	OLED_ShowCHinese(16,0,0);	//OLED显示  技
2853  0018 4b00          	push	#0
2854  001a ae1000        	ldw	x,#4096
2855  001d cd0000        	call	_OLED_ShowCHinese
2857  0020 84            	pop	a
2858                     ; 61 	OLED_ShowCHinese(32,0,1);	//OLED显示  新
2860  0021 4b01          	push	#1
2861  0023 ae2000        	ldw	x,#8192
2862  0026 cd0000        	call	_OLED_ShowCHinese
2864  0029 84            	pop	a
2865                     ; 62 	OLED_ShowCHinese(48,0,2);	//OLED显示  电
2867  002a 4b02          	push	#2
2868  002c ae3000        	ldw	x,#12288
2869  002f cd0000        	call	_OLED_ShowCHinese
2871  0032 84            	pop	a
2872                     ; 63 	OLED_ShowCHinese(64,0,3);	//OLED显示  子
2874  0033 4b03          	push	#3
2875  0035 ae4000        	ldw	x,#16384
2876  0038 cd0000        	call	_OLED_ShowCHinese
2878  003b 84            	pop	a
2879                     ; 64 	OLED_ShowCHinese(80,0,4);	//OLED显示  科
2881  003c 4b04          	push	#4
2882  003e ae5000        	ldw	x,#20480
2883  0041 cd0000        	call	_OLED_ShowCHinese
2885  0044 84            	pop	a
2886                     ; 65 	OLED_ShowCHinese(96,0,5);	//OLED显示  技
2888  0045 4b05          	push	#5
2889  0047 ae6000        	ldw	x,#24576
2890  004a cd0000        	call	_OLED_ShowCHinese
2892  004d 84            	pop	a
2893  004e               L3002:
2894                     ; 69 		PG_ODR ^= 0x03;	//异或 对 PG0 PG1 口取反
2896  004e c6501e        	ld	a,_PG_ODR
2897  0051 a803          	xor	a,	#3
2898  0053 c7501e        	ld	_PG_ODR,a
2899                     ; 70 		delay_ms(300);	//延迟300MS
2901  0056 ae012c        	ldw	x,#300
2902  0059 cd0000        	call	_delay_ms
2905  005c 20f0          	jra	L3002
2918                     	xdef	_main
2919                     	xref	_LED_Init
2920                     	xref	_delay_ms
2921                     	xref	_OLED_ShowCHinese
2922                     	xref	_OLED_ShowString
2923                     	xref	_OLED_Clear
2924                     	xref	_OLED_Init
2925                     .const:	section	.text
2926  0000               L1002:
2927  0000 4f4c45442054  	dc.b	"OLED TEST",0
2947                     	end
