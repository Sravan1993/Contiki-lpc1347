/*
 * Author  : Benjamin Vedder
 * Created : 2013-05-31
 */

#include "contiki.h"
#include "dev/leds.h"
#include "LPC13Uxx.h"

static int green_on = 0;
static int yellow_on = 0;
//static int red_on = 0;

void leds_arch_init(void) {
	//LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	GPIOSetDir( 1,14, 1 );
	GPIOSetDir( 1,13, 1 );
}

unsigned char leds_arch_get(void) {
	return (green_on ? 0 : LEDS_GREEN)
		| (yellow_on ? 0 : LEDS_YELLOW);
}

void leds_arch_set(unsigned char leds) {
	if(leds & LEDS_GREEN) {
		GPIOSetBitValue( 1,13, 1 );
		green_on = 1;
	} else {
		GPIOSetBitValue( 1,13, 0 );
		green_on = 0;
	}
	
	if(leds & LEDS_YELLOW) {
		GPIOSetBitValue( 1,14, 1 );
		yellow_on = 1;
	} else {
		GPIOSetBitValue( 1,13, 0 );
		yellow_on = 0;
	}
	
/*	if(leds & LEDS_RED) {
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		red_on = 1;
	} else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		red_on = 0;
	}
*/
}

