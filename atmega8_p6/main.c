//ICC-AVR application builder
//atmega8_p6
/*
    �\��G�p�ɾ�
        S1���s�G�C�q�\��̧�(�C�q¶����˴�)
        S2���s�G
                �Ĥ@�U�G��ܥثe����]��A��^
                �ĤG�U�G��ܥثe�ɶ��]�ɡA���^
                �ĤT�U�G��0000�p�ƨ�0010�]���j�@���^�A�����p�Ʈɦ^��S1���s�\��
*/
 
#include<iom8v.h>
#include<macros.h>

#define S_1      PORTC &= ~BIT(0);PORTC|=BIT(1) ;PORTC|=BIT(2) ;PORTC|=BIT(3); 
#define S_2      PORTC |= BIT(0) ;PORTC&=~BIT(1);PORTC|=BIT(2) ;PORTC|=BIT(3);
#define S_3      PORTC |= BIT(0) ;PORTC|=BIT(1) ;PORTC&=~BIT(2);PORTC|=BIT(3);  
#define S_4      PORTC |= BIT(0) ;PORTC|=BIT(1) ;PORTC|=BIT(2) ;PORTC&=~BIT(3);
#define S_OFF    PORTC |= BIT(0) ;PORTC|=BIT(1) ;PORTC|=BIT(2) ;PORTC|=BIT(3);  
#define S_ON     PORTC &= ~BIT(0);PORTC&=~BIT(1);PORTC&=~BIT(2);PORTC&=~BIT(3);

unsigned int seg[11] = 
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x71
};
 
unsigned int btn1_1[6] =
{
    0x01,0x02,0x04,0x08,0x10,0x20
};
 
unsigned int btn1_2[6] =
{
    0x20,0x10,0x08,0x04,0x02,0x01
};
 
unsigned int btn1_3[5] =
{
    0x03,0x06,0x0C,0x18,0x30
};
 
unsigned int btn1_4[5] =
{
    0x30,0x18,0x0C,0x06,0x03
};
 
unsigned int btn1_5[6] =
{
    0x01,0x03,0x07,0x0F,0x1F,0x3F
};
 
unsigned int btn1_6[6] =
{
    0x3F,0x1F,0x0F,0x07,0x03,0x01
};
 
unsigned int btn1_7[3] =
{
    0x0C,0x12,0x21
};
 
unsigned int btn1_8[3] =
{
    0x21,0x12,0x0C
};
 
unsigned int btn1_9[11] =
{
    0x01,0x02,0x04,0x08,0x10,0x20,0x10,0x08,0x04,0x02,0x01
};
 
unsigned int btn1_10[11] =
{
    0x20,0x10,0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x10,0x20
};
 
unsigned int btn1_index[10] =
{
    6,6,5,5,6,6,3,3,11,11
};
 
//��l�� �ܶq �n��//////////////////////////////////////////////////////////////
int data = 0;
int data2 = 0;
int i = 0;
int count = 0;
int count2 = 0;
 
void btn1_count(void)
{
 S_OFF;
    for(i=0;i<btn1_index[count];i++)
    {
        switch(count)
        {
            case 0:
                PORTC = ~btn1_1[i];
                delay_ms(1000);
            break;
            case 1:
                PORTC = ~btn1_2[i];
                delay_ms(1000);
            break;
            case 2:
                PORTC = ~btn1_3[i];
                delay_ms(1000);
            break;
            case 3:
                PORTC = ~btn1_4[i];
                delay_ms(1000);
            break;
            case 4:
                PORTC = ~btn1_5[i];
                delay_ms(1000);
            break;
            case 5:
                PORTC = ~btn1_6[i];
                delay_ms(1000);
            break;
            case 6:
                PORTC = ~btn1_7[i];
                delay_ms(1000);
            break;
            case 7:
                PORTC = ~btn1_8[i];
                delay_ms(1000);
            break;
            case 8:
                PORTC = ~btn1_9[i];
                delay_ms(1000);
            break;
            case 9:
                PORTC = ~btn1_10[i];
                delay_ms(1000);
            break;
        }
    }
    PORTC = 0xFF;
    count += 1;
   
    if(count == 10)
    {
        count = 1;
		timer0_open();
    }
}
 
void btn2(void)
{
    S_OFF;
    switch(count2)
    {
        case 0:PORTD = seg[0];S_ON;count2=1;break;
        case 1:PORTD = seg[10];S_ON;count2=0;break;
    }
}
 
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
					timer0_close();
                    btn1_count();
                break;//S1
               
                case 0X3B:
                    timer0_open();
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
 
void timer0_open(void)
{
    CLI();
    TCNT0 = 0x05;
    TIMSK |= BIT(TOIE0);
    TCCR0 |= BIT(CS01) | BIT(CS00);
    SEI();
}

void timer0_close(void)
{
	CLI();
    TIMSK &= ~BIT(TOIE0);
    TCCR0 &= ~(BIT(CS02) | BIT(CS01) | BIT(CS00));
    SEI();
}
 
//CPU�`���l��
void init_devices(void)
{
    CLI();
    port_init();
    MCUCR = 0x00;
    GICR  = 0x00;
   
    TIMSK = 0x00;
    TCCR0 = 0x00;
    TCNT0 = 0x05;
    SEI();
}
//�V�q��
#pragma interrupt_handler timer0_ovf_isr:10    
void timer0_ovf_isr(void)
{    
    TCNT0 = 0X05;
    data++;
    if(500==data)
    {
        data = 0;
        btn2();
    }
}
 
void main(void)
{
    init_devices();
    while(1)
    {  
        key_scan();
    }
}