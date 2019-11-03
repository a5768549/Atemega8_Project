//ICC-AVR application builder
//atmega8_p1
/*
	
		秙跑て
		S1祏陪ボLED:2
		S1陪ボLED:1
		S2材Ω陪ボLED:3
		S2材Ω陪ボLED:4癘魁材Ω
*/ 
 
#include <iom8v.h>
#include <macros.h>
 
#define LED PORTC
int flag = 0;
int count = 0;
/******************************************************************************* 
* ㄧ计嘿: delay_us()
* 把计: microsecond : 块┑稬丁
* 把计: 
* 磞瓃: 稬┑   	  	
*******************************************************************************/ 
void delay_us(unsigned int microsecond) 
{      
    do 
	{ 
        microsecond--; 
	}
    while (microsecond>1);
}
/******************************************************************************* 
* ㄧ计嘿: delay_ms()
* 把计: millisecond : 块┑睝丁
* 把计: 
* 磞瓃: 睝┑  	
*******************************************************************************/ 
void delay_ms(unsigned int millisecond) 
{      
    while (millisecond--)
	{
        delay_us(999);
	}
}
/******************************************************************************* 
* ㄧ计嘿: void key_scan(void)
* 把计: 
* 把计: 
* 磞瓃: 龄絃苯磞
*******************************************************************************/
void key_scan(void)
{
	PORTB = 0XFF;
	delay_ms(10);
	if((PINB&0x3F)!=0x3F)     //安1~8聋秙Τ砆(=0) 
	{ 
		delay_ms(20);
		if((PINB&0X3E) == 0X3E) //0X3E = S1秙
		{ 
			delay_ms(20);
			flag = 0;
			while((PINB) == 0X3E)
			{
				flag = flag + 1;
				delay_ms(50);
			}
			if(flag >= 20)
			{
				LED = ~1;
			}
			else if(flag <= 20)
			{
				LED = ~2;
			}
		}
		else if((PINB&0X3B) == 0X3B)//0X3B = S2秙
		{ 
			delay_ms(20);
			if(count == 0)
			{
				LED = 3;
				count = count + 1;
				delay_ms(100);
			}
			else if(count == 1)
			{
				LED = 4;
				count = 0;
				delay_ms(100);
			}
			//LED = 1 穦单 LED = 0XF1LED = 2 穦单 LED = 0XF2摸崩 
		}
	delay_ms(1);
	}
	
	PORTC |= BIT(4)|BIT(5);
	delay_ms(10);
	if((PINC&0x30)!=0x30)//0011 0000
	{
		delay_ms(20);
		if((PINC&0x30)!=0x30)
		{ 
			switch(PINC&0X30)//0001 0000
			{
				case 0X10:LED = 7;break;//S7
				case 0X20:LED = 3;break;//S3
				default:LED = 0XFF;break;
			}				
			delay_ms(1);
		}
	}

}
/******************************************************************************* 
* ㄧ计嘿: 
* 把计: 
* 把计: 
* 磞瓃: 
*******************************************************************************/ 
void port_int(void)
{
      //stop errant interrupts until set up
     CLI(); //disable all interrupts
     DDRB = 0XC0;//1100 0000
	 PORTB = 0XFF;
	 DDRC  = 0x3F;//0011 1111
     PORTC = 0xFF; 
	 MCUCR = 0x00;
	 GICR  = 0x00;
	 TIMSK = 0x00; //timer interrupt sources
	 SEI();
}
/****************************************************************************
ㄧ计:┑祘
把计:
把计:
****************************************************************************/
void delay(void)
{
 	 int i;
  	 for(i=0;i<200;i++);
}
/****************************************************************************
ㄧ计:祘
把计:
把计:
****************************************************************************/
void main(void)
{
	 port_int();
	 LED = 0XFF;
	 while(1)
	 {
	    key_scan(); 
	 }
}
