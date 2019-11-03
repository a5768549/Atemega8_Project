//ICC-AVR application builder
//atmega8_p1
/*
	�\��G
		���s���ܤ�
		S1�u���G���LED:2
		S1�����G���LED:1
		S2���Ĥ@���G���LED:3
		S2���ĤG���G���LED:4�A�P�ɰO���^��Ĥ@��
*/ 
 
#include <iom8v.h>
#include <macros.h>
 
#define LED PORTC
int flag = 0;
int count = 0;
/******************************************************************************* 
* ��ƦW��: delay_us()
* �J�f�Ѽ�: microsecond : ��J���ɷL���ɶ�
* �X�f�Ѽ�: 
* �\��y�z: �L������   	  	
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
* �J�f�Ѽ�: millisecond : ��J���ɲ@���ɶ�
* �X�f�Ѽ�: 
* �\��y�z: �@������  	
*******************************************************************************/ 
void delay_ms(unsigned int millisecond) 
{      
    while (millisecond--)
	{
        delay_us(999);
	}
}
/******************************************************************************* 
* ��ƦW��: void key_scan(void)
* �J�f�Ѽ�: 
* �X�f�Ѽ�: 
* �\��y�z: ��L���y
*******************************************************************************/
void key_scan(void)
{
	PORTB = 0XFF;
	delay_ms(10);
	if((PINB&0x3F)!=0x3F)     //���p1~8�����s���Q���U�h(=0) 
	{ 
		delay_ms(20);
		if((PINB&0X3E) == 0X3E) //0X3E = S1���s
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
		else if((PINB&0X3B) == 0X3B)//0X3B = S2���s
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
			//LED = 1 �|���� LED = 0XF1�ALED = 2 �|���� LED = 0XF2�A�H������ 
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
* ��ƦW��: 
* �J�f�Ѽ�: 
* �X�f�Ѽ�: 
* �\��y�z: 
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
��ƥ\��:���ɤl�{��
�J�f�Ѽ�:
�X�f�Ѽ�:
****************************************************************************/
void delay(void)
{
 	 int i;
  	 for(i=0;i<200;i++);
}
/****************************************************************************
��ƥ\��:�D�{��
�J�f�Ѽ�:
�X�f�Ѽ�:
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
