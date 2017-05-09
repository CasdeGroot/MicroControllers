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
#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>

typedef struct {
		unsigned char data;
		unsigned int delay;
	} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] =
{
	{0b10000001,200},{0b01000010,200},{0b00100100,200},{0b00011000,200},{0b00100100,200},{0b01000010,200},{0b10000001,200},
	{0b10000001,200},{0b01000010,200},{0b00100100,200},{0b00011000,200},{0b00100100,200},{0b01000010,200},{0b10000001,200},
	{0x00,0x00}
};



void wait(int ms);
void testBoard();
void assingment1();
void assingment2();
void assignment4();
void assignment5();
void assignment6();



int main (void)
{
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	DDRD = 0b11111111;
	/* Insert system clock initialization code here (sysclk_init()). */
	
	board_init();

	//testBoard();
	assignment6();

	/* Insert application code here, after the board has been initialized. */
	
	
	
	return 1;
}


void testBoard()
{
	
	while(1)
	{
		PORTD = 0b01010101;
		wait(2000);
		PORTD = 0b10101010;
		wait(2000);
		
	}
}

// Switches PortD pin 7 on and PortD pin 6 off every 500ms
void assingment1()
{
	while(1)
	{
		PORTD = 0b01000000;
		wait(500);
		PORTD = 0b00100000;
		wait(500);
		
	}
}

void assingment2()
{
	DDRC = 0b00000000;
	while(1)
	{
	if(PINC & 1)
	{
		PORTD = 0b01000000;
	}	
	else
	{
		PORTD = 0;
	}	
	
	}
}

void assignment4()
{
	PORTA = 0b00000001;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTD = 0b00000000;
	
	while(1)
	{
		wait(5);
		if(PORTA < 255)
		{
			PORTA = PORTA + 1;
		}
		else
		{
			PORTA = 1;
			if(PORTB < 255)
			{
				PORTB = PORTB + 1;
			}
			else
			{
				PORTB = 0;
				
				if(PORTC < 255)
				{
					PORTC = PORTC + 1;
				}
				else
				{
					PORTC = 0;
					
					if(PORTD < 255)
					{
						PORTD = PORTD + 1;	
					
					}
					else
					{
						PORTD = 0;
					
					}
				
				}
			}
		}
	}
}

void assignment5()
{
	while(1)
	{
		int index = 0;
		while(pattern[index].delay != 0)
		{
			PORTA = pattern[index].data;
			PORTC = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
		
	}	
}

void assignment6()
{
	int state = 1;
	
	while(1)
	{
		DDRC = 0b11111110;
		
		while(state == 1)
		{
			if(PINC & 1)
			{
				wait(1000);
				if(PINC & 1)
				{			
						state = 0;
				}
			}
			
			PORTC = 0b01000000;
			wait(1000);
			PORTC = 0b00000000;
			wait(1000);
		}
		
		while(state == 0)
		{
			if(PINC &1)
			{
				wait(1000);
				if(PINC & 1)
				{			
						state = 1;
				}
			}
			
			PORTC = 0b01000000;
			wait(250);
			PORTC = 0b00000000;
			wait(250);
		}
	}
}

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{ 
		_delay_ms(1);
	}
}
