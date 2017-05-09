/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ledmatrix.c
**
** Beschrijving:	Simple HT16K33 Ledmatix demo.
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ledmatrix.c
**					avr-gcc -g -mmcu=atmega128 -o ledmatrix.elf ledmatrix.o
**					avr-objcopy -O ihex ledmatrix.elf ledmatrix.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
* -------------------------------------------------------------------------*/
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define charA 0
#define charB 1
#define charC 2
#define charD 3
#define charE 4
#define charF 5
#define charG 6
#define charH 7
#define charI 8
#define charJ 9
#define charK 10
#define charL 11
#define charM 12
#define charN 13
#define charO 14
#define charP 15
#define charQ 16
#define charR 17
#define charS 18
#define charT 19
#define charU 20
#define charV 21
#define charW 22
#define charX 23
#define charY 24
#define charZ 25
#define num0 26
#define num1 27
#define num2 28
#define num3 29
#define num4 30
#define num5 31
#define num6 32
#define num7 33
#define num8 34
#define num9 35

int reverse(int);

// Number 0 to 9 with spaces in between
int NUMBERS[] =
{
 		
 		0b00000000,
 		0b00111100,
 		0b01100110,
 		0b01101110,
 		0b01110110,
 		0b01100110,
 		0b01100110,
 		0b00111100,
		0b00000000,
 		0b00000000,
 		0b00000000,
 		0b00011000,
 		0b00011000,
 		0b00111000,
 		0b00011000,
 		0b00011000,
 		0b00011000,
 		0b01111110,
 		0b00000000,
		0b00000000,
 		0b00000000,
 		0b00111100,
 		0b01100110,
 		0b00000110,
 		0b00001100,
 		0b00110000,
 		0b01100000,
 		0b01111110,
 		0b00000000,
		0b00000000,
 		0b00000000,
 		0b00111100,
 		0b01100110,
 		0b00000110,
 		0b00011100,
 		0b00000110,
 		0b01100110,
 		0b00111100,
 		0b00000000,
		0b00000000,
 		0b00000000,
 		0b00001100,
 		0b00011100,
 		0b00101100,
 		0b01001100,
 		0b01111110,
 		0b00001100,
 		0b00001100,
 		0b00000000,
		0b00000000,
 		0b00000000,
 		0b01111110,
 		0b01100000,
 		0b01111100,
 		0b00000110,
 		0b00000110,
 		0b01100110,
 		0b00111100,
 		0b00000000,
		0b00000000,
 		0b00000000,
 		0b00111100,
 		0b01100110,
 		0b01100000,
 		0b01111100,
 		0b01100110,
 		0b01100110,
 		0b00111100,
 		0b00000000,
		0b00000000,
 		0b00000000,
 		0b01111110,
 		0b01100110,
 		0b00001100,
 		0b00001100,
 		0b00011000,
 		0b00011000,
 		0b00011000,
 		0b00000000,
		0b00000000,
 		0b00000000,
 		0b00111100,
 		0b01100110,
 		0b01100110,
 		0b00111100,
 		0b01100110,
 		0b01100110,
 		0b00111100,
 		0b00000000,
		0b00000000,
 		0b00000000,
 		0b00111100,
 		0b01100110,
 		0b01100110,
 		0b00111110,
 		0b00000110,
 		0b01100110,
 		0b00111100
};

int IMAGES[][8] = {
	{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01100110,
		0b01111110,
		0b01100110,
		0b01100110,
		0b01100110
		},{
		0b00000000,
		0b01111100,
		0b01100110,
		0b01100110,
		0b01111100,
		0b01100110,
		0b01100110,
		0b01111100
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100110,
		0b00111100
		},{
		0b00000000,
		0b01111100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01111100
		},{
		0b00000000,
		0b01111110,
		0b01100000,
		0b01100000,
		0b01111100,
		0b01100000,
		0b01100000,
		0b01111110
		},{
		0b00000000,
		0b01111110,
		0b01100000,
		0b01100000,
		0b01111100,
		0b01100000,
		0b01100000,
		0b01100000
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01100000,
		0b01100000,
		0b01101110,
		0b01100110,
		0b00111100
		},{
		0b00000000,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01111110,
		0b01100110,
		0b01100110,
		0b01100110
		},{
		0b00000000,
		0b00111100,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00111100
		},{
		0b00000000,
		0b00011110,
		0b00001100,
		0b00001100,
		0b00001100,
		0b01101100,
		0b01101100,
		0b00111000
		},{
		0b00000000,
		0b01100110,
		0b01101100,
		0b01111000,
		0b01110000,
		0b01111000,
		0b01101100,
		0b01100110
		},{
		0b00000000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01100000,
		0b01111110
		},{
		0b00000000,
		0b01100011,
		0b01110111,
		0b01111111,
		0b01101011,
		0b01100011,
		0b01100011,
		0b01100011
		},{
		0b00000000,
		0b01100011,
		0b01110011,
		0b01111011,
		0b01101111,
		0b01100111,
		0b01100011,
		0b01100011
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b00111100
		},{
		0b00000000,
		0b01111100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01111100,
		0b01100000,
		0b01100000
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01101110,
		0b00111100,
		0b00000110
		},{
		0b00000000,
		0b01111100,
		0b01100110,
		0b01100110,
		0b01111100,
		0b01111000,
		0b01101100,
		0b01100110
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01100000,
		0b00111100,
		0b00000110,
		0b01100110,
		0b00111100
		},{
		0b00000000,
		0b01111110,
		0b01011010,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00011000
		},{
		0b00000000,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b00111110
		},{
		0b00000000,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b01100110,
		0b00111100,
		0b00011000
		},{
		0b00000000,
		0b01100011,
		0b01100011,
		0b01100011,
		0b01101011,
		0b01111111,
		0b01110111,
		0b01100011
		},{
		0b00000000,
		0b01100011,
		0b01100011,
		0b00110110,
		0b00011100,
		0b00110110,
		0b01100011,
		0b01100011
		},{
		0b00000000,
		0b01100110,
		0b01100110,
		0b01100110,
		0b00111100,
		0b00011000,
		0b00011000,
		0b00011000
		},{
		0b00000000,
		0b01111110,
		0b00000110,
		0b00001100,
		0b00011000,
		0b00110000,
		0b01100000,
		0b01111110
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01101110,
		0b01110110,
		0b01100110,
		0b01100110,
		0b00111100
		},{
		0b00000000,
		0b00011000,
		0b00011000,
		0b00111000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b01111110
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b00000110,
		0b00001100,
		0b00110000,
		0b01100000,
		0b01111110
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b00000110,
		0b00011100,
		0b00000110,
		0b01100110,
		0b00111100
		},{
		0b00000000,
		0b00001100,
		0b00011100,
		0b00101100,
		0b01001100,
		0b01111110,
		0b00001100,
		0b00001100
		},{
		0b00000000,
		0b01111110,
		0b01100000,
		0b01111100,
		0b00000110,
		0b00000110,
		0b01100110,
		0b00111100
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01100000,
		0b01111100,
		0b01100110,
		0b01100110,
		0b00111100
		},{
		0b00000000,
		0b01111110,
		0b01100110,
		0b00001100,
		0b00001100,
		0b00011000,
		0b00011000,
		0b00011000
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01100110,
		0b00111100,
		0b01100110,
		0b01100110,
		0b00111100
		},{
		0b00000000,
		0b00111100,
		0b01100110,
		0b01100110,
		0b00111110,
		0b00000110,
		0b01100110,
		0b00111100
	}};


const int IMAGES_LEN = sizeof(IMAGES)/8;

// index of the number array
int indexNumberArray = 0;


/**********/
void twi_init(void)
/* 
short:			Init AVR TWI interface and set bitrate
inputs:			
outputs:	
notes:			TWI clock is set to 100 kHz
Version :    	DMK, Initial code
*********/
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

/**********/
void twi_start(void)
/* 
short:			Generate TWI start condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*********/
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

/**********/
void twi_stop(void)
/* 
short:			Generate TWI stop condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*********/
{
	TWCR = (0x80 | 0x10 | 0x04);
}

/**********/
void twi_tx(unsigned char data)
/* 
short:			transmit 8 bits data
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*********/
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}


void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

// Clears the whole 8x8 dot matrix
void clear (void)
{
	int row = 7;

	for(int i = 0; i <= row; i++)
	{
		
			twi_start();
			twi_tx(0xE0);	// Display I2C addres + R/W bit
			twi_tx(i*2);	// Address
			twi_tx(00);	// data
			twi_stop();
		
	}
}

// Fills whole 8x8 dot matrix
void fill(void)
{
	int row = 7;

	for(int i = 0; i <= row;i++)
	{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(i*2);	// Address
		twi_tx(1);	// data
		wait(5000);
		twi_stop();
	}
}


// Commands to init the dot matrix
void initcommands(void)
{
	
	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();
}

// Draws pixels in the given row
void drawPixel(int row, int data)
{
	twi_start();
	twi_tx(0xE0);
	twi_tx(row*2);
	twi_tx(data);
	twi_stop();
}

// reverses a byte eg. 0b11110000 becomes 0b00001111
int reverse(int byte)
{
	
	byte = (byte * 0x0202020202ULL & 0x010884422010ULL) % 1023;
	return byte;

}

// Draws 8 rows.
void drawArray(int byteArray[])
{
	for (int i = 0; i < 8; i++)
	{
		int byte = reverse(byteArray[i]);
		twi_start();
		twi_tx(0xE0);
		twi_tx(i*2);
		twi_tx(byte);
		twi_stop();
	}
}

// Draws 8 rows with an given index, this makes it possible to scroll chars.
void scrollVertical(int byteArray[],int index)
{
	for (int i = 0; i < 8; i++)
	{
		int byte = reverse(byteArray[index + i]);
		twi_start();
		twi_tx(0xE0);
		twi_tx(i*2);
		twi_tx(byte);
		twi_stop();
	}
}


// Draws all letters of the alphabeth and numbers 0 to 9 on the 8x8 matrix
void testAlphabet()
{
	for(int i = 0; i<36; i++)
	{
		drawArray(IMAGES[i]);
		wait(1000);
	}
}


int main( void )
{
	
	twi_init();		// Init TWI interface
	initcommands();	// Standard commands before running 
	clear();
	
	int i = 0;
	while (1)
	{
			wait(250);
			clear();
			scrollVertical(NUMBERS, i);
			i++;
			if(i > 90)		// if all elements of number have been displayed -> reset
			{
			  i = 0;
			}

	}

	return 1;
}