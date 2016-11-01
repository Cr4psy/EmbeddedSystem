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
#include "main.h"


int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	
	board_init();
	//Init I/O
	AVR32_GPIO.port[1].gpers = 0xF0F << 19;//Enable GPIO
	AVR32_GPIO.port[1].oders = 0xF0F << 19;//enable output driver
	AVR32_GPIO.port[1].ovrc = 0xF0F << 19;//clear all value
	AVR32_GPIO.port[1].ovrs = 0xF0F << 19;//Turn off all leds
	
	AVR32_GPIO.port[2].gpers = 1 << 24; //Enable GPIO
	
	// Insert application code here, after the board has been initialized.
		
	while (1)
	{
		//task11();//Turn on all the leds
		
		int input = (AVR32_GPIO.port[2].pvr >> 24) & 0x01;//Read button1
		
		//task12(input);//Switch one led with button 1
		//task13(input);//Switch color when press and release
		//task14(input);//Switch color when pressed
		task15((AVR32_GPIO.port[2].pvr >> 18) & 0x049;);//Read all buttons once
		

		
	}

}
