
#include "asf.h"
#define EXAMPLE_PWM_PIN			AVR32_PWM_3_PIN
#define EXAMPLE_PWM_FUNCTION	AVR32_PWM_3_FUNCTION

/* Connection of the light sensor */
#  define EXAMPLE_ADC_LIGHT_CHANNEL           2
#  define EXAMPLE_ADC_LIGHT_PIN               AVR32_ADC_AD_2_PIN
#  define EXAMPLE_ADC_LIGHT_FUNCTION          AVR32_ADC_AD_2_FUNCTION

/** GPIO pin/adc-function map. */
const gpio_map_t ADC_GPIO_MAP = {

	{EXAMPLE_ADC_LIGHT_PIN, EXAMPLE_ADC_LIGHT_FUNCTION},
};

int main(void) {
	
	board_init();
	/* Init system clocks */
	sysclk_init();
	/* init debug serial line */
	init_dbg_rs232(sysclk_get_cpu_hz());
	
	unsigned int channel_id = 3;
	signed short adc_value_light = -1;
	avr32_pwm_channel_t pwm_channel = { .ccnt = 0 }; // One channel config.
	
	gpio_enable_module_pin(EXAMPLE_PWM_PIN, EXAMPLE_PWM_FUNCTION);
	pwm_channel.CMR.cpre = AVR32_PWM_CPRE_MCK_DIV_8; //Channel prescaler.
	pwm_channel.cdty = 1; // Channel duty cycle, should be <CPRD.
	pwm_channel.cmr = 0;
	pwm_channel.CMR.cpd = 0;
	pwm_channel.cprd = 20; // Channel period.
	// With these settings, the output waveform period will be :
	// (115200/8)/20 == 760Hz == (MCK/prescaler)
	pwm_channel_init(channel_id, &pwm_channel); // Set channel configuration to channel 3.
	pwm_start_channels(1 << channel_id); // Start channel 3.
	
	/* Assign and enable GPIO pins to the ADC function. */
	gpio_enable_module(ADC_GPIO_MAP, sizeof(ADC_GPIO_MAP)/sizeof(ADC_GPIO_MAP[0]));
	
		/* Configure the ADC peripheral module.
	 * Lower the ADC clock to match the ADC characteristics (because we
	 * configured the CPU clock to 12MHz, and the ADC clock characteristics are
	 *  usually lower; cf. the ADC Characteristic section in the datasheet). */
	AVR32_ADC.mr |= 0x1 << AVR32_ADC_MR_PRESCAL_OFFSET;
	adc_configure(&AVR32_ADC);
	/* Enable the ADC channels. */
	adc_enable(&AVR32_ADC, EXAMPLE_ADC_LIGHT_CHANNEL);
	
	/* Display a header to user */
	//print_dbg("\x1B[2J\x1B[H\r\nADC Example\r\n");
	
	while(1){
		
		/* Start conversions on all enabled channels */
		adc_start(&AVR32_ADC);
		
		/* Get value for the light adc channel */
		adc_value_light = 500;//adc_get_value(&AVR32_ADC,EXAMPLE_ADC_LIGHT_CHANNEL);
	
		//pwm_channel.cdty = (20/1024)*adc_value_light; // Channel duty cycle, should be <CPRD.
		pwm_channel.CMR.cpd = 0;
		pwm_channel.cmr = 0;
		pwm_channel.cupd = (20/1024)*adc_value_light;
		pwm_async_update_channel(channel_id, &pwm_channel);
		//pwm_channel_init(channel_id, &pwm_channel); // Set channel configuration to channel 3.
		//pwm_start_channels(1 << channel_id); // Start channel 3.
		/* Slow down the display of converted values */
		LED_Toggle((LED0));
		delay_ms(500);
		
	}
	return 0;
}