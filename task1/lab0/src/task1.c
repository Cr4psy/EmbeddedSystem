//Program
#include <asf.h>

void task11()
{
	AVR32_GPIO.port[1].ovrc = 0xF0F << 19;
}


void task12(int input)
{
	static int preVal;
	static int x;
	
	if (preVal==0 && input==1)//Rising edge
	{
		if (x==0)
		{
			AVR32_GPIO.port[1].ovrc = 1 << 19;
			x=1;
		}
		else if (x==1)
		{
			AVR32_GPIO.port[1].ovrs = 1 << 19;
			x=0;
		}
	}
	
	preVal=input;
	
}

void task13(int input)
{
	if (input==1)//Rising edge
	{

		AVR32_GPIO.port[1].ovrc = 1 << 19;
		AVR32_GPIO.port[1].ovrs = 1 << 20;

	}
	else
	{
		AVR32_GPIO.port[1].ovrs = 1 << 19;
		AVR32_GPIO.port[1].ovrc = 1 << 20;
	}
		
}

void task14(int input)
{
	static int preVal;
	static int x;
	
	if (preVal==0 && input==1)//Rising edge
	{
		if (x==0)
		{
			AVR32_GPIO.port[1].ovrc = 1 << 19;
			AVR32_GPIO.port[1].ovrs = 1 << 20;
			x=1;
		}
		else if (x==1)
		{
			AVR32_GPIO.port[1].ovrs = 1 << 19;
			AVR32_GPIO.port[1].ovrc = 1 << 20;
			x=0;
		}
	}
	
	preVal=input;
	
}


void task15(U32 readVal)
{
		/*
		if ((readVal >> 3*0) & 0b01)
		{
			AVR32_GPIO.port[1].ovrs = 1 << 27 ;//Turn on led
		}
		else
		{
			AVR32_GPIO.port[1].ovrc = 1 << 27 ;//Turn off led
		}*/
		
		U32 myMask = (readVal & 0b01) | (readVal >> 2 & 0b010) | (readVal >> 4 & 0b0100);	
		AVR32_GPIO.port[1].ovr = myMask << 27; // Each button is allocated to one led.
}