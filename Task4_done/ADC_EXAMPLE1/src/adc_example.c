
#include <asf.h>
#include "conf_example.h"

/** GPIO pin/adc-function map. */
const gpio_map_t ADC_GPIO_MAP = {

	{EXAMPLE_ADC_LIGHT_PIN, EXAMPLE_ADC_LIGHT_FUNCTION},
};

/** \brief Main application entry point - init and loop to display ADC values */
int main(void)
{


	signed short adc_value_light = -1;


	board_init();
	
	/* Init system clocks */
	sysclk_init();

	/* init debug serial line */
	init_dbg_rs232(sysclk_get_cpu_hz());

	/* Assign and enable GPIO pins to the ADC function. */
	gpio_enable_module(ADC_GPIO_MAP, sizeof(ADC_GPIO_MAP) /
			sizeof(ADC_GPIO_MAP[0]));

	/* Configure the ADC peripheral module.
	 * Lower the ADC clock to match the ADC characteristics (because we
	 * configured the CPU clock to 12MHz, and the ADC clock characteristics are
	 *  usually lower; cf. the ADC Characteristic section in the datasheet). */
	//AVR32_ADC.mr |= 0x1 << AVR32_ADC_MR_PRESCAL_OFFSET;
	adc_configure(&AVR32_ADC);

	/* Enable the ADC channels. */
	adc_enable(&AVR32_ADC, EXAMPLE_ADC_LIGHT_CHANNEL);

	/*Configure LED*/
	
	
	
	/* Display a header to user */
	print_dbg("\x1B[2J\x1B[H\r\nADC Example\r\n");

	while (true) {
		/* Start conversions on all enabled channels */
		adc_start(&AVR32_ADC);




		/* Get value for the light adc channel */
		adc_value_light = adc_get_value(&AVR32_ADC,
				EXAMPLE_ADC_LIGHT_CHANNEL);
		
		/* Display value to user */
		print_dbg("HEX Value for Channel light : 0x");
		print_dbg_hex(adc_value_light);
		print_dbg("\r\n");
		
		if (adc_value_light<0x005)
		{
			LED_Display(0b0000);
		}
		else if (adc_value_light<0x0A0)
		{
			LED_Display(0b0001);
		}
		else if (adc_value_light<0x0100)
		{
			LED_Display(0b0011);
		}
		else if (adc_value_light<0x0300)
		{
			LED_Display(0b0111);
		}
		else
		{
			LED_Display(0b1111);
		}

		/* Slow down the display of converted values */
		delay_ms(500);
	}

	return 0;
}
