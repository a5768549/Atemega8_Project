//ICC-AVR application builder
//atmega8_p3
/*
	功能：
		預設在七段顯示器顯示ADC7可變電阻值 
		按鈕按第一下：七段顯示器從ADC7值跑到0 
		按鈕按第二下：七段顯示器從0跑到ADC7值，同時記錄回到第一下 
*/ 
#include<iom8v.h>
#include<macros.h>

#define S_1      PORTC&=~BIT(0);PORTC|=BIT(1);PORTC|=BIT(2);PORTC|=BIT(3); 
#define S_2      PORTC|=BIT(0);PORTC&=~BIT(1);PORTC|=BIT(2);PORTC|=BIT(3);
#define S_3      PORTC|=BIT(0);PORTC|=BIT(1);PORTC&=~BIT(2);PORTC|=BIT(3);  
#define S_4      PORTC|=BIT(0);PORTC|=BIT(1);PORTC|=BIT(2);PORTC&=~BIT(3);
#define S_OFF    PORTC|=BIT(0);PORTC|=BIT(1);PORTC|=BIT(2);PORTC|=BIT(3);  
#define S_ON     PORTC&=~BIT(0);PORTC&=~BIT(1);PORTC&=~BIT(2);PORTC&=~BIT(3);

unsigned char tab[16] = 
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
						 
//初始化 變量 聲明//////////////////////////////////////////////////////////////
unsigned char cnn = 0;//定時器變量
unsigned char i   = 0;//數碼管位選用
unsigned int  j   = 0;
unsigned char ad  = 0;//AD採集間隔
unsigned int ad_data2=0;
int count = 0;
int flag  = 0;
int th  = 0;
int hu  = 0;
int ten = 0;
int num = 0;

void de_led(void)
{
	S_OFF;
	th = ad_data2 / 1000;
	PORTD = tab[th];
	S_1;
	delay_ms(1);

	S_OFF;
	hu = (ad_data2 / 100) % 10;
	PORTD = tab[hu]|0x80;
	S_2;
	delay_ms(1);

	S_OFF;
	ten = (ad_data2 / 10) % 10;
	PORTD = tab[ten];
	S_3;
	delay_ms(1);

	S_OFF;
	num = ad_data2 % 10;
	PORTD = tab[num];
	S_4;
	delay_ms(1);
}
void btn1(void)
{
	flag = ad_chane(ad_cat());
	for(j = flag;j>0;j--)
	{
	 	S_OFF;
	 	th = j / 1000;
		PORTD = tab[th];
		S_1;
		delay_ms(2);

		S_OFF;
		hu = (j / 100) % 10;
		PORTD = tab[hu]|0x80;
		S_2;
		delay_ms(2);

		S_OFF;
		ten = (j / 10) % 10;
		PORTD = tab[ten];
		S_3;
		delay_ms(2);

		S_OFF;
		num = j % 10;
		PORTD = tab[num];
		S_4;
		delay_ms(1);
	}
}

void btn2(void)
{
	flag = ad_chane(ad_cat());
 	for(j = 0;j<flag;j++)
	{
		S_OFF;
		th = j / 1000;
		PORTD = tab[th];
		S_1;
		delay_ms(2);
		S_OFF;
		hu = (j / 100) % 10;
		PORTD = tab[hu]|0x80;
		S_2;
		delay_ms(2);
		S_OFF;
		ten = (j / 10) % 10;
		PORTD = tab[ten];
		S_3;
		delay_ms(2);
		S_OFF;
		num = j % 10;
		PORTD = tab[num];
		S_4;
		delay_ms(1);
	}
}

void key_scan(void)
{
 	delay_ms(20);
	if((PINB&0x3F)!=0x3F)     //假如1~8顆按鈕有被按下去(=0) 
	{ 
		delay_ms(20);
		if((PINB&0X3B) == 0X3B)//0X3B = S2按鈕
		{ 
			delay_ms(20);
			if(count == 0)
			{
				btn1();
				count = count + 1;
				delay_ms(100);
			}
			else if(count == 1)
			{
				btn2();
				count = 0;
				delay_ms(100);
			}
			//LED = 1 會等於 LED = 0XF1，LED = 2 會等於 LED = 0XF2，以此類推 
		}
	}
}
/******************************************************************************* 
* 函數名稱: delay_us()
* 入口參數: microsecond : 輸入延時微秒的時間
* 出口參數: 
* 功能描述: 微秒的延時   	  	
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
* 函數名稱: delay_ms()
* 入口參數: millisecond : 輸入延時毫秒的時間
* 出口參數: 
* 功能描述: 毫秒的延時  	
*******************************************************************************/ 
void delay_ms(unsigned int millisecond) 
{      
    while (millisecond--)
	{
        delay_us(999);
	}  
}

//I、O口初始化
void por_init(void)
{
   DDRB  = 0XC0;//1100 0000
   PORTB = 0XFF;
   PORTD = 0XFF;
   DDRD = 0XFF;
   PORTC = 0X0F;//AD採集口 ADC 設置為輸入
   DDRC = 0X0F;
   
}

void display(unsigned char n)
{
    PORTD = tab[n];
}

void display1(unsigned char n)
{
    PORTD = tab[n]|0X80;
}

//定時器0初始化
void timer0_int(void)
{
    TCCR0 =(1<<CS01) | (1<<CS00);
	TCNT0 = 0X05;
	TIMSK = 0x01; //T0/C0溢出中斷使能
}

//CPU總體初始化
void init_devices(void)
{
   por_init();
   timer0_int();
   SEI();
}
 
unsigned int ad_cat(void)//電壓採集函數
{
    unsigned int t1,t2;
	ADCSRA = 0X00;//disable adc
	ADMUX=0x07;//ref  左對齊  ADC7
	ACSR = 0x80;//使能adc可用，不用修改
	ADCSRA|=BIT(ADEN);           
	ADCSRA|=BIT(ADSC);           
	while(!(ADCSRA&(BIT(ADIF))));
    ADCSRA&=~BIT(ADIF);
    t1 = (unsigned int)ADCL;
    t2 = (unsigned int)ADCH;
    t2 = (t2<<8)+t1;
    return t2;
}

unsigned int ad_chane(unsigned int i)//電壓轉換函數
{
   long x;
   unsigned int y;
   x = (2500*(long)i)/1024;
   y = (unsigned int)x;
   return y;
}
 
//定時器0///////////////////////////////////////////////////////////////////////
#pragma interrupt_handler timer0_ovf_isr:10
void timer0_ovf_isr(void)
{    
   TCNT0 = 0X05;//內部晶振，幾分頻算出時間初值
   ad++;
   if(50==ad)//AD採集
   {
    	ad=0;
		ad_data2=ad_chane(ad_cat());
   }
}//end of void timer0_ovf_isr(void)

void main(void)
{
   init_devices();
   while(1)
   { 
		key_scan();
		de_led();
   }
}