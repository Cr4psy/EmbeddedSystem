/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>

int main (void)
{
	int preVal=0;
	int x=0;
	// Insert system clock initialization code here (sysclk_init()).

	board_init();

	// Insert application code here, after the board has been initialized.
	while(1)
	{	
		
		int readVal = gpio_get_pin_value(GPIO_PUSH_BUTTON_0);

		if(preVal == 0 && readVal == 1)//Rising edge
		{
			//LED_Toggle(0b1011);//Toogle led 1 2 and 4	
			
			//Togle all the leds with personnal toggle
			/*
			if (x==0)
			{
				x=1;
				LED_On(0b1111);
			}
			else if (x==1)
			{
				x=0;
				LED_Off(0b1111);
			}
			*/
			

			LED_Display(0b1010);
			
			/*With LED_on or LED_Off, we choose which led we want to turn on or off. However if we want to turn half led on and half led off, we have to use both function.
			With the displaz function, we choose not the state of the leds, not which led. So we set all the led directly.
			*/
			
		}

		preVal = readVal;
		
	}
}
