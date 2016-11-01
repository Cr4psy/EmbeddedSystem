
#include <asf.h>
#include <stdio.h>

void task21(int LED[])
{
	int i;
	for(i=0; i<8; i++)
	{
		gpio_clr_gpio_pin(LED[i]);
	}
	
}

void task22(int LED[], int Switch[])
{
	static int x;
	static int preVal;
	int i = gpio_get_pin_value(Switch[0]);
	if(preVal==0 && i==1){
		if (x==1)
		{
			gpio_set_gpio_pin(LED[0]);
			x=0;
		}
		else if (x==0)
		{
			gpio_clr_gpio_pin(LED[0]);
			x=1;
		}
	}
	preVal=i;	
}

void task23(int LED[], int Switch[])
{
	static int x;
	static int preVal;
	int i = gpio_get_pin_value(Switch[0]);
	if(preVal==0 && i==1){
		if (x==1)
		{
			gpio_set_gpio_pin(LED[5]);
			gpio_clr_gpio_pin(LED[4]);
			x=0;
		}
		else if (x==0)
		{
			gpio_clr_gpio_pin(LED[5]);
			gpio_set_gpio_pin(LED[4]);
			x=1;
		}
	}
	preVal=i;	
}


void task24(int LED[], int Switch[])
{

	int i = gpio_get_pin_value(Switch[0]);

	if (i==1)
	{
		gpio_set_gpio_pin(LED[5]);
		gpio_clr_gpio_pin(LED[4]);

	}
	else if (i==0)
	{
		gpio_clr_gpio_pin(LED[5])			;
		gpio_set_gpio_pin(LED[4]);

	}
	
}


void task25(int LED[], int Joystick[])
{
	int right = gpio_get_pin_value(Joystick[3]);
	int left = gpio_get_pin_value(Joystick[0]);
	int push = gpio_get_pin_value(Joystick[4]);
	static int preValRight;
	static int preValLeft;
	int i;
	static int num;
	int maxVal=3;
	//printf("%d", Joystick);
	
	if (preValRight==0 && right==1)
	{
		num++;
	}
	preValRight = right;
	if (preValLeft==0 && left==1)
	{
		num--;
	}
	preValLeft=left;
	if (num<0)
	{
		num=maxVal;
	}
	if (num>maxVal)
	{
		num=0;
	}
	
	for (i=0; i<8; i++)
	{
		gpio_set_gpio_pin(LED[i]);
	}
	gpio_clr_gpio_pin(LED[num]);
	
	if (!push)
	{
		for (i=0; i<4; i++)
		{
			gpio_clr_gpio_pin(LED[i]);
		}
	}
		
}