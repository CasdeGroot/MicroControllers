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
#define F_CPU 8000000
#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void wait( int ms );
void count7segDisplay();

int counter = 0;

const unsigned char nummers[16] =
{
	//		Pgfe	dcba		// nummer op display

		
		0b00111111,		// 0
		0b00000110,		// 1
		0b01011011,		// 2
		0b01001111,		// 3
		0b01100110,		// 4
		0b01101101,		// 5
		0b01111101,		// 6
		0b00000111,		// 7
		0b01111111,		// 8
		0b01101111,	    // 9
		0b01110111,		// A
		0b01111111,		// B
		0b00001111,		// C
		0b01011110,		// D
		0b01111001,		// E
		0b01110001		// F


	

};

// Wanneer er op D0 of D1 gedrukt wordt wordt er een teller opgehoogd of verminderd.
// Hierna wordt de 7 seg display aangestuurd.
// Echter 1 probleem is dat de knopjes soms bij 1x indrukken meerdere keren worden getriggerd
// Dit is ook al in eerdere opgaves voorgekomen en ik weet niet hoe ik dit moet fixen.
ISR( INT0_vect)
{
	if(counter < 25)
	counter = counter + 1;
	if(counter > 14)
	{
		PORTB = nummers[14];
	}
	else
	{
		PORTB = nummers[counter];
	}
	wait(150);
}

ISR( INT1_vect)
{
	if(counter > 0)
	{
		counter = counter - 1;
	}
	PORTB = nummers[counter];
	wait(150);
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();

	DDRB = 0b11111111; // Alles op output
	DDRD = 0b00000000; // Alles wordt op input

	EICRA |= 0b00001111; 
	EIMSK |= 0b00000011; // Zet INT1 en INT2 aan
	sei();

	
	while(1)
	{
		
			wait(500);	
		
	}

	return 1;
}

// Deze functie laat de 7 segment display omhoog tellen
// na 14 laat hij de letter E zien.
void count7segDisplay()
{
	while(1)
	{

		for (int i = 0; i < 16; i++)
		{
			if(i > 14)
			{
				PORTB = nummers[14];
			}
			else
			{
				PORTB = nummers[i];
			}
			
			wait(500);
		}
	}
}

void wait( int ms )

{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

