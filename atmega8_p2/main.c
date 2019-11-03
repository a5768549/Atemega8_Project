//ICC-AVR application builder
//atmega8_p2
/*
	�\��G
		�w�]�]�C�q��ܾ��j��
		���s���Ĥ@�U�G�C�q��ܾ��q0000�]��9999
		���s���ĤG�U�G�C�q��ܾ��q9999�]��6666�A�P�ɰO���^��Ĥ@�U 
*/ 

#include<iom8v.h>
#include<macros.h>

#define S_1      PORTC &= ~BIT(0);PORTC|=BIT(1) ;PORTC|=BIT(2) ;PORTC|=BIT(3); 
#define S_2      PORTC |= BIT(0) ;PORTC&=~BIT(1);PORTC|=BIT(2) ;PORTC|=BIT(3);
#define S_3      PORTC |= BIT(0) ;PORTC|=BIT(1) ;PORTC&=~BIT(2);PORTC|=BIT(3);  
#define S_4      PORTC |= BIT(0) ;PORTC|=BIT(1) ;PORTC|=BIT(2) ;PORTC&=~BIT(3);
#define S_OFF    PORTC |= BIT(0) ;PORTC|=BIT(1) ;PORTC|=BIT(2) ;PORTC|=BIT(3);  
#define S_ON     PORTC &= ~BIT(0);PORTC&=~BIT(1);PORTC&=~BIT(2);PORTC&=~BIT(3);

#define w1       PORTD =  0x01; S_1;
#define w2 		 PORTD =  0x01; S_2;
#define w3		 PORTD =  0x01; S_3;
#define w4		 PORTD =  0x01; S_4;	
#define w5		 PORTD =  0x02; S_4;		
#define w6		 PORTD =  0x04; S_4;	
#define w7		 PORTD =  0x08; S_4;
#define w8		 PORTD =  0x08; S_3;	
#define w9		 PORTD =  0x08; S_2;	
#define w10		 PORTD =  0x08; S_1;		
#define w11		 PORTD =  0x10; S_1;		
#define w12		 PORTD =  0x20; S_1;	
	
unsigned int seg[10] = 
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f
};

//��l�� �ܶq �n��//////////////////////////////////////////////////////////////
int data = 0;
int flag = 0;
int count = 0;
int th = 0;
int hu = 0;
int ten = 0;
int num = 0;
int i = 0;
int j = 0;
void key_scan(void)
{
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
void btn1(void)
{
 	for(i = 0;i<10000;i++)
	{
		for(j = 0;j<20;j++)
		{
			S_OFF;
			th = i / 1000;
			PORTD = seg[th];
			S_1;
			delay_ms(1);
			S_OFF;
			hu = (i / 100) % 10;
			PORTD = seg[hu];
			S_2;
			delay_ms(1);
			S_OFF;
			ten = (i / 10) % 10;
			PORTD = seg[ten];
			S_3;
			delay_ms(1);
			S_OFF;
			num = i % 10;
			PORTD = seg[num];
			S_4;
			delay_ms(1);
		}
	}
}

void btn2(void)
{
 	 for(i = 9999;i>6665;i--)
	 {
	 	for(j = 0;j<20;j++)
		{
			S_OFF;
			th = i / 1000;
			PORTD = seg[th];
			S_1;
			delay_ms(1);
			S_OFF;
			hu = (i / 100) % 10;
			PORTD = seg[hu];
			S_2;
			delay_ms(1);
			S_OFF;
			ten = (i / 10) % 10;
			PORTD = seg[ten];
			S_3;
			delay_ms(1);
			S_OFF;
			num = i % 10;
			PORTD = seg[num];
			S_4;
			delay_ms(1);
		}
	}
}

void w(void)
{
	switch(flag)
	{
		case 1 : w1;break;
		case 2 : w2;break;
		case 3 : w3;break;
		case 4 : w4;break;
		case 5 : w5;break;
		case 6 : w6;break;
		case 7 : w7;break;
		case 8 : w8;break;
		case 9 : w9;break;
		case 10:w10;break;
		case 11:w11;break;
		case 12:w12;break;
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

//I�BO�f��l��
void port_init(void)
{
 DDRB  = 0XC0;//1100 0000
 PORTB = 0XFF;
 PORTC = 0xFF; //m103 output only
 DDRC  = 0xFF;
 PORTD = 0xFF;
 DDRD  = 0xFF;
}

//�w�ɾ�0��l��
void timer0_int(void)
{
    TIMSK = 0x01; //T0/C0���X���_�ϯ�
	TCCR0 =(1<<CS01) | (1<<CS00);
	TCNT0 = 0X05;//0XFF   256    (0xFF-0X05) *8M/64
	
}
//CPU�`���l��
void init_devices(void)
{
 CLI();
 port_init();
 MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x00;
 timer0_int();
 SEI();
}

#pragma interrupt_handler timer0_ovf_isr:10
void timer0_ovf_isr(void)
{    
	TCNT0 = 0X05;//���������A�X���W��X�ɶ����
	data++;
	if(500 == data)// 500*(255-5)*(8M/64)=T
	{
		data = 0;
		S_OFF;
		w();
		flag = flag + 1;
		if(flag == 13)flag = 1;
	}
}//end of void timer0_ovf_isr(void)


void main(void)
{
   init_devices();
   S_OFF;
   while(1)
   {   
		key_scan();
   }
}
