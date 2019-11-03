//ICC-AVR application builder
//atmega8_p4
/*
	�\��G�p�ɾ� 
		S1���s�G�]�w�ɶ�(�q0000�V�W�ơA��}�Y��) 
		S2���s�G�}�l�˼�(timer�}��) 
		S4���s�G�Ȱ��˼�(timer����)
		S6���s�G����˼Ƴt��(�q0000�V�W�ơA��}�Y���A�ƭȥi�q0~100)
		�˼Ʀ�0000�ɰ{�{�T�U 
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

//��l�� �ܶq �n��//////////////////////////////////////////////////////////////
int data = 0;
int flag = 0;
int th = 0;
int hu = 0;
int ten = 0;
int num = 0;
int i = 0;
int speed = 50;
int again = 0;

void key_scan(void)
{
	if((PINB&0x3F)!=0x3F)     //���p1~8�����s���Q���U�h(=0) 
	{ 
	  	if((PINB&0x3F)!=0x3F)
        { 
			delay_ms(20);
			switch(PINB)
			{
				case 0X3E:
					while((PINB) == 0X3E)
						{
							flag = flag + 1;
							up_count();
				
							if(flag == 9999)
							{
				 				flag = 0;
							}
							delay_ms(10);
						}
				break;//S1
				
				case 0X3B:
					timer0_open();
				break;//S2
				
				case 0X37:
					while((PINB) == 0X37)
					{
						speed = speed + 1;
						speed_count();

						if(speed == 100)
						{
				 			speed = 0;
						}
						delay_ms(20);
					}
				break;//S6
				
				case 0X3D:
					timer0_close();
				break;//S4
					
				default:break;
			}				
			delay_ms(1);
		}
	}
}

void stop_fuc(void)
{
	if(again == 1)
	{
	    timer0_close();
		for(i = 0;i<3;i++)
		{
			S_OFF;
			delay_ms(500);
			S_ON;
			delay_ms(500);
		}
		again = 0;
		flag = 0;
	}
}

void speed_count(void)
{
 	for(i = 0;i<40;i++)
	{
	 	S_OFF;
	 	th = speed / 1000;
	 	PORTD = seg[th];
	 	S_1;
	 	delay_us(500);
	 	S_OFF;
	 	hu = (speed / 100) % 10;
	 	PORTD = seg[hu];
	 	S_2;
	 	delay_us(500);
	 	S_OFF;
	 	ten = (speed / 10) % 10;
	 	PORTD = seg[ten];
	 	S_3;
	 	delay_us(500);
	 	S_OFF;
	 	num = speed % 10;
	 	PORTD = seg[num];
	 	S_4;
	 	delay_us(500);
	}
}

void up_count(void)
{
  	S_OFF;
	th = flag / 1000;
	PORTD = seg[th];
	S_1;
	delay_us(900);
	S_OFF;
	hu = (flag / 100) % 10;
	PORTD = seg[hu];
	S_2;
	delay_us(900);
	S_OFF;
	ten = (flag / 10) % 10;
	PORTD = seg[ten]|0x80;
	S_3;
	delay_us(900);
	S_OFF;
	num = flag % 10;
	PORTD = seg[num];
	S_4;
	delay_us(900);
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
 DDRB  = 0XC0;
 PORTB = 0XFF;//���s 
 
 PORTC = 0xFF;
 DDRC  = 0xFF;
 PORTD = 0xFF;
 DDRD  = 0xFF;//�C�q��ܾ� 
}

void timer0_close(void)
{
 	CLI();
    TIMSK = 0x01;
	TCCR0 =(0<<CS01) | (0<<CS00);
	TCNT0 = 0X05;//0XFF   256    (0xFF-0X05) *8M/64
	SEI();
}

void timer0_open(void)
{
 	CLI();
    TIMSK = 0x01;
	TCCR0 =(1<<CS01) | (1<<CS00);
	TCNT0 = 0X05;					//timer�_�l��(255-5) 
	SEI();
}

//CPU�`���l��
void init_devices(void)
{
 CLI();
 port_init();
 MCUCR = 0x00;
 GICR  = 0x00;

 TIMSK = 0x01;
 TCCR0 =(0<<CS01) | (0<<CS00);
 TCNT0 = 0X05;
 
 SEI();
}
//�V�q�� 
#pragma interrupt_handler timer0_ovf_isr:10		
void timer0_ovf_isr(void)
{    
	TCNT0 = 0X05;
	data++;
	
	if(data == speed && again == 0)				// 50*(255-5)*(8M/64)=0.1s
	{
		data = 0;
		flag -= 1;
		if(flag == 0)
		{
			again = 1;
		}
		up_count();
		S_OFF;
	}
}


void main(void)
{
   init_devices();
   S_OFF;
   while(1)
   {   
		key_scan();
		up_count();
		stop_fuc();
   }
}