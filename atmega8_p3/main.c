//ICC-AVR application builder
//atmega8_p3
/*
	�\��G
		�w�]�b�C�q��ܾ����ADC7�i�ܹq���� 
		���s���Ĥ@�U�G�C�q��ܾ��qADC7�ȶ]��0 
		���s���ĤG�U�G�C�q��ܾ��q0�]��ADC7�ȡA�P�ɰO���^��Ĥ@�U 
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
						 
//��l�� �ܶq �n��//////////////////////////////////////////////////////////////
unsigned char cnn = 0;//�w�ɾ��ܶq
unsigned char i   = 0;//�ƽX�ަ���
unsigned int  j   = 0;
unsigned char ad  = 0;//AD�Ķ����j
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
	if((PINB&0x3F)!=0x3F)     //���p1~8�����s���Q���U�h(=0) 
	{ 
		delay_ms(20);
		if((PINB&0X3B) == 0X3B)//0X3B = S2���s
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
			//LED = 1 �|���� LED = 0XF1�ALED = 2 �|���� LED = 0XF2�A�H������ 
		}
	}
}
/******************************************************************************* 
* ��ƦW��: delay_us()
* �J�f�Ѽ�: microsecond : ��J���ɷL�����ɶ�
* �X�f�Ѽ�: 
* �\��y�z: �L��������   	  	
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
* ��ƦW��: delay_ms()
* �J�f�Ѽ�: millisecond : ��J���ɲ@�����ɶ�
* �X�f�Ѽ�: 
* �\��y�z: �@��������  	
*******************************************************************************/ 
void delay_ms(unsigned int millisecond) 
{      
    while (millisecond--)
	{
        delay_us(999);
	}  
}

//I�BO�f��l��
void por_init(void)
{
   DDRB  = 0XC0;//1100 0000
   PORTB = 0XFF;
   PORTD = 0XFF;
   DDRD = 0XFF;
   PORTC = 0X0F;//AD�Ķ��f ADC �]�m����J
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

//�w�ɾ�0��l��
void timer0_int(void)
{
    TCCR0 =(1<<CS01) | (1<<CS00);
	TCNT0 = 0X05;
	TIMSK = 0x01; //T0/C0���X���_�ϯ�
}

//CPU�`���l��
void init_devices(void)
{
   por_init();
   timer0_int();
   SEI();
}
 
unsigned int ad_cat(void)//�q���Ķ����
{
    unsigned int t1,t2;
	ADCSRA = 0X00;//disable adc
	ADMUX=0x07;//ref  �����  ADC7
	ACSR = 0x80;//�ϯ�adc�i�ΡA���έק�
	ADCSRA|=BIT(ADEN);           
	ADCSRA|=BIT(ADSC);           
	while(!(ADCSRA&(BIT(ADIF))));
    ADCSRA&=~BIT(ADIF);
    t1 = (unsigned int)ADCL;
    t2 = (unsigned int)ADCH;
    t2 = (t2<<8)+t1;
    return t2;
}

unsigned int ad_chane(unsigned int i)//�q���ഫ���
{
   long x;
   unsigned int y;
   x = (2500*(long)i)/1024;
   y = (unsigned int)x;
   return y;
}
 
//�w�ɾ�0///////////////////////////////////////////////////////////////////////
#pragma interrupt_handler timer0_ovf_isr:10
void timer0_ovf_isr(void)
{    
   TCNT0 = 0X05;//���������A�X���W��X�ɶ����
   ad++;
   if(50==ad)//AD�Ķ�
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