#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* sei() :致能中斷 */
#include <util/delay.h>     /* _delay_ms() */


#include <avr/pgmspace.h>   /* usbdrv.h 所需的參數定義 */
#include "usbdrv.h"
#include "oddebug.h"        /* 使用除錯巨集的範例 */

#include "config.h"

unsigned int timer[3];
int testpin = 0;
int seg_pin = 0;
volatile int seg_vb[4];
void Delay_ms(unsigned int S);
void InitPort(void);
/* ----------------------------- USB interface ----------------------------- */
PROGMEM const char usbHidReportDescriptor[22] =
{/* USB 報告描述元 */
	0x06, 0x00, 0xff,              // USAGE_PAGE (販售商自定)
	0x09, 0x01,                    // USAGE (Vendor Usage 1)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x95, 0x80,                    //   REPORT_COUNT (128)
	0x09, 0x00,                    //   USAGE (Undefined)
	0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
	0xc0                           // END_COLLECTION
};

static uchar    currentAddress;
static uchar    bytesRemaining;

uchar	usbFunctionRead(uchar *data, uchar len)       //寫給VB的值
{
	if(len > bytesRemaining)
	{
		len = bytesRemaining;
	}
	if(currentAddress == 0)
	{
		*(data)   = 0;
		*(data+1) = testpin;
		*(data+2) = 0;
		*(data+3) = 0;
		*(data+4) = 0;
		*(data+5) = 0;
		*(data+6) = 0;
		*(data+7) = 0;
	}
	currentAddress += len;
	bytesRemaining -= len;
	return len;
}

uchar   usbFunctionWrite(uchar *data, uchar len)     //讀VB值
{
	if(bytesRemaining == 0)
	{
		return 1;
	}
	if(len > bytesRemaining)
	{
		len = bytesRemaining;
	}
	
	if(currentAddress == 0)
	{
		if(data[0] ==  1)//讀值為1
		{
			if(testpin == 0)
			{
				testpin = 1;
			}
			else
			{
				testpin = 0;
			}
		}
		if(data[0] ==  2)//讀值為2
		{
				seg_pin = 1;
				seg_vb[0] = data[1];
				seg_vb[1] = data[2];
				seg_vb[2] = data[3];
				seg_vb[3] = data[4];
		}
		if(data[0] ==  3)//讀值為2
		{
			seg_pin = 0;
		}
	}
	currentAddress += len;
	bytesRemaining -= len;
	return bytesRemaining == 0;
}

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	usbRequest_t    *rq = (void *)data;
	if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS)
	{
		if(rq->bRequest == USBRQ_HID_GET_REPORT)
		{
			bytesRemaining = 8;
			currentAddress = 0;
			return USB_NO_MSG;
		}
		else if(rq->bRequest == USBRQ_HID_SET_REPORT)
		{
			bytesRemaining = 8;
			currentAddress = 0;
			return USB_NO_MSG;
		}
	}
else
{
		/* ignore vendor type requests, we don't use any */
}
	return 0;
}

/*********************************/
/*                               */
/*        主    程    式         */
/*                               */
/*********************************/


int main(void)
{
	InitPort();
	for(;;)
	{
		Delay_ms(100);
		if(testpin == 1)
		{
			PORTC |= _BV(0);
		}else
		{
			PORTC &= ~_BV(0);
		}
		
		if(seg_pin == 1)
		{
			if (!(TIMSK & _BV(TOIE1))) //檢查Timer1的中斷是否開啟, 沒有的話才執行
			{
				timer1_open();
			}
		}
		if(seg_pin == 0)
		{
			if (TIMSK & _BV(TOIE1)) //檢查Timer1的中斷是否開啟, 有的話才執行
			{
				timer1_close();
				S_OFF;
			}
		}
	}
	return 0;
}


/*********************************/
/*                               */
/*        副    程    式         */
/*                               */
/*********************************/
void Delay_ms(unsigned int S)
{
	while(S--)
	{
		usbPoll();
		wdt_reset();
		_delay_ms(1);
	}
}
//腳位、中斷初始化
void InitPort(void)
{
	uchar i;
	wdt_enable(WDTO_1S);
	/* IO SETUP */

	DDRB = 0x3F;
	DDRC = 0x5F;
	DDRD = 0xEA;     //PD2 PD4 為USB資料腳，不能改變

	usbInit();
	usbDeviceDisconnect();
	i = 0;
	while(--i)
	{
		wdt_reset();
		_delay_ms(1);
	}
	usbDeviceConnect();
	
	TIMSK &= ~_BV(TOIE1);
	TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
	
	sei();
}
/*********************************/
/*                               */
/*     中  斷  副  程  式        */
/*                               */
/*********************************/
ISR (TIMER0_OVF_vect)
{
	TCNT0 = 22;
	if (timer[1]-- == 0)
	{
		timer[1]=50;
		ADCSRA |= (1 << ADSC);
		wdt_reset();
	}
}

ISR (TIMER1_OVF_vect)
{
	TCNT1H = 0xFF;
	TCNT1L = 0x00;
	if (timer[2]-- == 0)
	{
		timer[2]=50;
		seg_split(seg_vb[0],seg_vb[1],seg_vb[2],seg_vb[3]);
	}
}
