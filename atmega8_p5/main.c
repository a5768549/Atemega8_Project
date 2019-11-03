//ICC-AVR application builder
//atmega8_p4
/*
	功能：計時器 
		S1按鈕：七段功能依序(七段繞圈圈檢測)
		S2按鈕：
				第一下：顯示目前日期（月，日）
				第二下：顯示目前時間（時，分）
				第三下：由0000計數到0010（間隔一秒），結束計數時回到S1按鈕功能
*/ 

#include<iom8v.h>
#include<macros.h>

#define S_1      PORTC &= ~BIT(0);PORTC|=BIT(1) ;PORTC|=BIT(2) ;PORTC|=BIT(3); 
#define S_2      PORTC |= BIT(0) ;PORTC&=~BIT(1);PORTC|=BIT(2) ;PORTC|=BIT(3);
#define S_3      PORTC |= BIT(0) ;PORTC|=BIT(1) ;PORTC&=~BIT(2);PORTC|=BIT(3);  
#define S_4      PORTC |= BIT(0) ;PORTC|=BIT(1) ;PORTC|=BIT(2) ;PORTC&=~BIT(3);
#define S_OFF    PORTC |= BIT(0) ;PORTC|=BIT(1) ;PORTC|=BIT(2) ;PORTC|=BIT(3);  
#define S_ON     PORTC &= ~BIT(0);PORTC&=~BIT(1);PORTC&=~BIT(2);PORTC&=~BIT(3);

unsigned int seg[10] = 
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f
};

//初始化 變量 聲明//////////////////////////////////////////////////////////////
int data = 0;
int data2 = 0;

int count = 1;
int count_num = 1;
int btn2_count = 1;
int btn2_3_count = 0;
int btn2_3_flag = 0;

void btn2_1(void)
{
	int i = 0;
	S_OFF;
	for(i = 0;i<500;i++)
	{
	PORTD = seg[0];S_1;
	delay_ms(1);
	PORTD = seg[7];S_2;
	delay_ms(1);
	PORTD = seg[2];S_3;
	delay_ms(1);
	PORTD = seg[4];S_4;
	delay_ms(1);
	}
	S_OFF;
	btn2_count = 2;
}

void btn2_2(void)
{
	int i = 0;
	S_OFF;
	for(i = 0;i<500;i++)
	{
	PORTD = seg[0];S_1;
	delay_ms(1);
	PORTD = seg[2];S_2;
	delay_ms(1);
	PORTD = seg[5];S_3;
	delay_ms(1);
	PORTD = seg[6];S_4;
	delay_ms(1);
	}
	S_OFF;
	btn2_count = 3;
}

void btn2_3(void)
{
	int th = 0;
	int hu = 0;
	int ten = 0;
	int num = 0;
	int i = 0;
	S_OFF;

	th = btn2_3_count / 1000;
	PORTD = seg[th];
	S_1;
	delay_ms(1);
	hu = (btn2_3_count / 100) % 10;
	PORTD = seg[hu];
	S_2;
	delay_ms(1);
	ten = (btn2_3_count / 10) % 10;
	PORTD = seg[ten];
	S_3;
	delay_ms(1);
	num = btn2_3_count % 10;
	PORTD = seg[num];
	S_4;
	delay_ms(1);

}

void btn1_fuc(void)
{
	switch(count_num)
	{
		case 1 : S_1;break;
		case 2 : S_2;break;
		case 3 : S_3;break;
		case 4 : S_4;break;
	}
	
}

void btn1(void)
{
	if ((1 <= count) && (count <= 8))
	{
		PORTD = 1 << (count - 1); 
	}
	btn1_fuc();
}

void key_scan(void)
{
	if((PINB&0x3F)!=0x3F)     //假如1~8顆按鈕有被按下去(=0) 
	{ 
	  	if((PINB&0x3F)!=0x3F)
        { 
			delay_ms(20);
			switch(PINB)
			{
				case 0X3E:
					timer0_open();
				break;//S1
				
				case 0X3B:
					timer0_close();
					switch(btn2_count)
					{
						case 1:btn2_1();break;
						case 2:btn2_2();break;
						case 3:
							timer2_open();
							btn2_count = 99;
						break;
					}
				break;//S2
				default:break;
			}				
			delay_ms(1);
		}
	}
}

void delay_us(unsigned int microsecond) 
{      
    do 
	{ 
		microsecond--; 
	}         
    while (microsecond>1); 
}

void delay_ms(unsigned int millisecond) 
{      
    while (millisecond--)
	{
		delay_us(999);
	}  
}

//I、O口初始化
void port_init(void)
{
	DDRB  = 0XC0;
	PORTB = 0XFF;//按鈕 
 
	PORTC = 0xFF;
	DDRC  = 0xFF;
	PORTD = 0xFF;
	DDRD  = 0xFF;//七段顯示器 
}

void timer0_close(void)
{
	CLI();
    TIMSK &= ~BIT(TOIE0);
    TCCR0 &= ~(BIT(CS02) | BIT(CS01) | BIT(CS00));
    SEI();
}

void timer0_open(void)
{
	CLI();
    TCNT0 = 0x05;
    TIMSK |= BIT(TOIE0);
    TCCR0 |= BIT(CS01) | BIT(CS00);
    SEI();
}

void timer2_close(void)
{
	CLI();
    TIMSK &= ~BIT(TOIE2);
    TCCR2 &= ~(BIT(CS22) | BIT(CS21) | BIT(CS20));
    SEI();
}

void timer2_open(void)
{
	CLI();
    TCNT2 = 0x83;
    TIMSK |= BIT(TOIE2);
    TCCR2 |= BIT(CS22);
    SEI();
}

//CPU總體初始化
void init_devices(void)
{
	CLI();
    port_init();
    MCUCR = 0x00;
    GICR  = 0x00;
	
    TIMSK = 0x00;
    TCCR0 = 0x00;
    TCNT0 = 0x05;
	
    TCCR2 = 0x00;
    TCNT2 = 0x83;
    SEI();
}
//向量值 
#pragma interrupt_handler timer0_ovf_isr:10		
void timer0_ovf_isr(void)
{    
	TCNT0 = 0X05;
	data++;
	
	if(data == 50)
	{
		if(count == 9)
		{
			count = 1;
			count_num += 1;
		}
		if(count_num == 5)
		{
			count_num = 1;
		}
		data = 0;
		S_OFF;
		btn1();
		count = count + 1;
	}
}

#pragma interrupt_handler timer2_ovf_isf:5
void timer2_ovf_isf(void)
{
	TCNT2 = 0X05;//初值
	data2++;

	if(data2 == 500)
	{
		if(btn2_3_flag == 0)
		{
			btn2_3_flag =1;
		}
		data2 = 0;
		btn2_3_count += 1;
		if(btn2_3_count == 11)
		{
			btn2_3_count = 0;
			btn2_count = 1;
			btn2_3_flag = 0;
			timer2_close();
			timer0_open();
		}	
		S_OFF;
	}
}

void main(void)
{
	SREG = 0X80;
	init_devices();
	while(1)
	{   
		key_scan();
		if(btn2_3_flag == 1)
		{
			btn2_3();
		}
	}
}