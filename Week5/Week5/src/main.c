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
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#define F_CPU 8000000

#define BIT(x)	(1 << (x))

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	//board_init();

	// uncomment lines under the opgave number

	
	// opgave 1
	//DDRF = 0x00;		// ADC alles op input
	//DDRA = 0xFF;		// om lichtjes te laten branden
	//DDRB = 0xFF;

	// opgave 2 & 3
	//DDRF = 0x00;
	//DDRA = 0xFF;


	

	//opgave 1
	//ADMUX = 0b01100001;		// AREF= VCC result left adjusted channel1 at pin pf1
	//ADCSRA = 0b11100110;	// ADC aanzetten, geen intterupt, aan en 64 scale
 
	//opgave 2
	//ADMUX = 0b11100001;	
	//ADCSRA = 0b10000110;

	//opgave 3
	//ADMUX = 0b11100001;
	//ADCSRA = 0b11100110;
		//init_lcd_4bit();
		//wait(300);
		//char tempToDisplay[15];
		//clearScreen();

	while(1)
	{
		//opgave 1
		//PORTA = ADCH;
		//PORTB = ADCL;


		//opgave 2
		ADCSRA |= BIT(6);			// Starten ADC
		while (ADCSRA & BIT(6));	// wachten
		PORTA = ADCH;
		wait(500);
		
		//opgave 3
		/*clearScreen();
		int i = ADCH;
		sprintf(tempToDisplay, "%i°C", i);
		wait(5);
		
		display_text(tempToDisplay);
		wait(5);
		memset(tempToDisplay, 0, 15);
		PORTA = ADCH;
		wait(2000); */
		
	}

	return 1;
	/* Insert application code here, after the board has been initialized. */
}
