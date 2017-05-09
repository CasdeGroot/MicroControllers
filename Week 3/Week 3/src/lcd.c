#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h" 

#define LCD_E 	3
#define LCD_RS	2

//int main (void)
//{
	//DDRD = 0xFF;
//
	//init_4bit_mode();
//
	//
	////set_cursor(7);
	////scroll_right();
	////set_cursor(8);
	////scroll_right();
	////scroll_right();
	//clear_screen();
	//write_string_lcd("123456");
	//set_cursor(2);
	//while(1)
	//{
		//PORTD ^= (1<<7);	// Toggle PORTD.7
		//_delay_ms( 250 );
		//
		////scroll_text_left();
		//
//
		//
	//}
//
//
	//return 1;
//}

void toggle_e_pin(void)
{
		//PORTC = 0x40;	//0b0100
		//wait(1);
		//PORTC = 0x00;	//0b0000
		//wait(1);
		PORTC |= (1<<LCD_E);	// E high
		_delay_ms(1);			// nodig
		PORTC &= ~(1<<LCD_E);  	// E low
		_delay_ms(1);
}

void init_4bit_mode(void)
{
		// Alles op output mode en alles op laag
		DDRC = 0xFF;
		PORTC = 0x00;

		
		PORTC = 0x20;	// 4 bits mode 1 line
		toggle_e_pin();

		
		PORTC = 0x20;   // 4 bits mode 2 lines
		toggle_e_pin();
		PORTC = 0x80;
		toggle_e_pin();

	
		PORTC = 0x00;   // cursor knipperen
		toggle_e_pin();
		PORTC = 0xF0;
		toggle_e_pin();

	
		PORTC = 0x00;   // Entry mode
		toggle_e_pin();
		PORTC = 0x60;
		toggle_e_pin();

	


}


/*
// First nibble.
PORTC = 0x1E;
PORTC &= ~(1<<LCD_RS);
toggle_e_pin();

// Second nibble
PORTC = (0x1E<<4);
PORTC &= ~(1<<LCD_RS);
toggle_e_pin();

 */


void scroll_text_right(void)
{
	//PORTC = 0x10;
	//toggle_e_pin();
	//PORTC = 0xE0;
	//toggle_e_pin();
	lcd_write_command(0x1C);
	
}

void scroll_text_left(void)
{
	//PORTC = 0x10;
	//toggle_e_pin();
	//PORTC = 0x80;
	//toggle_e_pin();
	lcd_write_command(0x18);
	
}


void set_cursor(int position)
{
	if(position > 0)
	{
		for(int i = 0; i < position; i++)
		{
			lcd_write_command(0x14);
		}
	}
	else
	{
		for(int i = 0; i < position; i++)
		{
			lcd_write_command(0x10);
		}
	}
}


void write_string_lcd(char *string)
{
	clear_screen();
	_delay_ms(20);
	for(;*string; string++){
		write_data_lcd(*string);
	}
}

void clear_screen(void)
{
	lcd_write_command(0x01);
	lcd_write_command(0x10);
	lcd_write_command(0x80);
}

void write_data_lcd(unsigned char byte)
{
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	toggle_e_pin();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	toggle_e_pin();
	_delay_ms(50);

}


void lcd_write_command(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	toggle_e_pin();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	toggle_e_pin();
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		
	}
}