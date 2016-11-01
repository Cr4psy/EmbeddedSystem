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

#define AVR32_ADC_ADDRESS                  0xFFFF3C00
#define AVR32_ADC                          (*((volatile avr32_adc_t*)AVR32_ADC_ADDRESS))


#define DBG_USART_BAUDRATE   57600

/* The resolution of the A/D converter is 10bit so 1024 steps. (p.699) Can also be configured with 8bits.*/
int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
		/* Init system clocks */
		sysclk_init();
		/* init debug serial line */
		init_dbg_rs232(DBG_USART_BAUDRATE);
		board_init();

			
		gpio_enable_gpio_pin(AVR32_ADC_AD_2_PIN);//Enable light detector
		adc_configure(&AVR32_ADC);		
		adc_start(&AVR32_ADC);
		
		signed short adc_value_light  = -1;
		/* Display a header to user */
		print_dbg("\x1B[2J\x1B[H\r\nADC Example\r\n");
	// Insert application code here, after the board has been initialized.
		while(true)
		{
			adc_value_light = adc_get_value(&AVR32_ADC, 2);
		
			/* Display value to user */
			print_dbg("HEX Value for Channel light : 0x");
			print_dbg_hex(adc_value_light);
			print_dbg("\r\n");
		

			/* Slow down the display of converted values */
			delay_ms(500);
		}
		return 0;
}


	
	
