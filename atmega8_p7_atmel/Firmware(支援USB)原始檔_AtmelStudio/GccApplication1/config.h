#ifndef CONFIG_H_
#define CONFIG_H_

#define S_1 PORTC |= _BV(1);PORTC |= _BV(2);PORTC |= _BV(3);
#define S_2 PORTC |= _BV(1);PORTC |= _BV(2);PORTC &= ~_BV(3);
#define S_3 PORTC |= _BV(1);PORTC &= ~_BV(2);PORTC |= _BV(3);
#define S_4 PORTC |= _BV(1);PORTC &= ~_BV(2);PORTC &= ~_BV(3);
#define S_OFF PORTC &= ~_BV(1);PORTC |= _BV(2);PORTC &= ~ _BV(3);

#define seg_enable PORTC &= ~ _BV(1);PORTC |= _BV(2);PORTC |= _BV(3);

#define A0 PORTB |= _BV(0);
#define A1 PORTB |= _BV(1);
#define A2 PORTB |= _BV(2);
#define A3 PORTB |= _BV(3);
#define A4 PORTB |= _BV(4);
#define A5 PORTB |= _BV(5);
#define A6 PORTD |= _BV(6);
#define A7 PORTD |= _BV(7);

#define B0 PORTB &= ~_BV(0);
#define B1 PORTB &= ~_BV(1);
#define B2 PORTB &= ~_BV(2);
#define B3 PORTB &= ~_BV(3);
#define B4 PORTB &= ~_BV(4);
#define B5 PORTB &= ~_BV(5);
#define B6 PORTD &= ~_BV(6);
#define B7 PORTD &= ~_BV(7);

#define seg_clear B0;B1;B2;B3;B4;B5;B6;B7;seg_enable;

#define seg0 A0;A1;A2;A3;A4;A5;B6;B7;seg_enable;
#define seg1 B0;A1;A2;B3;B4;B5;B6;B7;seg_enable;
#define seg2 A0;A1;B2;A3;A4;B5;A6;B7;seg_enable;
#define seg3 A0;A1;A2;A3;B4;B5;A6;B7;seg_enable;
#define seg4 B0;A1;A2;B3;B4;A5;A6;B7;seg_enable;
#define seg5 A0;B1;A2;A3;B4;A5;A6;B7;seg_enable;
#define seg6 A0;B1;A2;A3;A4;A5;A6;B7;seg_enable;
#define seg7 A0;A1;A2;B3;B4;A5;B6;B7;seg_enable;
#define seg8 A0;A1;A2;A3;A4;A5;A6;B7;seg_enable;
#define seg9 A0;A1;A2;B3;B4;A5;A6;B7;seg_enable;

void seg_select(int x)
{
	switch(x)
	{
		case 0:seg0;break;
		case 1:seg1;break;
		case 2:seg2;break;
		case 3:seg3;break;
		case 4:seg4;break;
		case 5:seg5;break;
		case 6:seg6;break;
		case 7:seg7;break;
		case 8:seg8;break;
		case 9:seg9;break;
	}
}

void seg_split(int w,int x,int y,int z)
{
	S_OFF;
	seg_select(w);
	S_4;
	_delay_ms(1);
	seg_select(x);
	S_3;
	_delay_ms(1);
	seg_select(y);
	S_2;
	_delay_ms(1);
	seg_select(z);
	S_1;
	_delay_ms(1);
}

void seg(int x)
{
	int th = 0;
	int hu = 0;
	int ten = 0;
	int num = 0;

	th = (x / 1000) % 10;
	hu = (x / 100) % 10;
	ten = (x / 10) % 10;
	num = x % 10;
	seg_split(th,hu,ten,num);
}

void timer1_close(void)
{
	cli();
	TIMSK &= ~_BV(TOIE1);
	TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
	sei();
}

void timer1_open(void)
{
	cli();
	TCNT1H = 0xFF;
	TCNT1L = 0x00;
	TIMSK |= _BV(TOIE1);
	TCCR1B &= ~ _BV(CS12);
	TCCR1B |= _BV(CS11);
	TCCR1B &= ~ _BV(CS10);
	sei();
}

#endif /* CONFIG_H_ */