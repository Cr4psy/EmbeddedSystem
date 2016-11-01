
#include <asf.h>
#include "task2.h"

int LED[] = {59, 60, 61, 62, 51, 52, 53, 54};
int Switch[] = {88, 85, 82};
int Joystick[] = {25,26,27,28,20};



	
int main (void)
{
	board_init();
	
	int i;
	for(i=0;  i<8; i++)
	{
		gpio_enable_gpio_pin(LED[i]);
	}
	
	for(i=0; i<3; i++)
	{
		gpio_enable_gpio_pin(Switch[i]);
	}
	for(i=0; i<5; i++)
	{
		gpio_enable_gpio_pin(Joystick[i]);
	}
	
	
	while(1)
	{
		//task21(LED);
		//task22(LED, Switch);
		//task23(LED, Switch);
		//task24(LED, Switch);
		task25(LED, Joystick);
	
		
	}

}
