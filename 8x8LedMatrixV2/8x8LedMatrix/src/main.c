/*
Title: 8x8 dot matrix scrolling
By: Joshua Latusia and Cas de Groot
Date: 2017-03-30
Description:	This is our project we made for our micro controllers assignment
				By adding chars to the "string[]" you can display a string on the 8x8 dot matrix.
*/


#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

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
#define space 36

int reverse(int);

int IMAGES[][8] = {
	{
		0b00000000, //A
		0b01111000,
		0b11001100,
		0b11001100,
		0b11111100,
		0b11001100,
		0b11001100,
		0b11001100
		},{
		0b00000000, //B
		0b11111000,
		0b11001100,
		0b11001100,
		0b11111000,
		0b11001100,
		0b11001100,
		0b11111000
		},{
		0b00000000,//C
		0b01111000,
		0b11001100,
		0b11000000,
		0b11000000,
		0b11000000,
		0b11001100,
		0b01111000
		},{
		0b00000000,//D
		0b11111000,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11111000
		},{
		0b00000000,//E
		0b11111100,
		0b11000000,
		0b11000000,
		0b11111000,
		0b11000000,
		0b11000000,
		0b11111100
		},{
		0b00000000,//F
		0b11111100,
		0b11000000,
		0b11000000,
		0b11111000,
		0b11000000,
		0b11000000,
		0b11000000
		},{
		0b00000000,//G
		0b01111000,
		0b11001100,
		0b11000000,
		0b11000000,
		0b11011100,
		0b11001100,
		0b01111000
		},{
		0b00000000,//H
		0b11001100,
		0b11001100,
		0b11001100,
		0b11111100,
		0b11001100,
		0b11001100,
		0b11001100
		},{
		0b00000000,//I
		0b01111000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b01111000
		},{
		0b00000000,//J
		0b00111100,
		0b00011000,
		0b00011000,
		0b00011000,
		0b11011000,
		0b11011000,
		0b01110000
		},{
		0b00000000, //K
		0b11001100,
		0b11011000,
		0b11110000,
		0b11100000,
		0b11110000,
		0b11011000,
		0b11001100
		},{
		0b00000000, //L
		0b11000000,
		0b11000000,
		0b11000000,
		0b11000000,
		0b11000000,
		0b11000000,
		0b11111100
		},{
		0b00000000, //M
		0b11000110,
		0b11101110,
		0b11111110,
		0b11010110,
		0b11000110,
		0b11000110,
		0b11000110
		},{
		0b00000000,//N
		0b11000110,
		0b11100110,
		0b11110110,
		0b11011110,
		0b11001110,
		0b11000110,
		0b11000110
		},{
		0b00000000,//O
		0b01111000,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b01111000
		},{
		0b00000000,//P
		0b11111000,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11111000,
		0b11000000,
		0b11000000
		},{
		0b00000000,//Q
		0b01111000,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11011100,
		0b01111000,
		0b00001100
		},{
		0b00000000,//R
		0b11111000,
		0b11001100,
		0b11001100,
		0b11111000,
		0b11110000,
		0b11011000,
		0b11001100
		},{
		0b00000000,//S
		0b01111000,
		0b11001100,
		0b11000000,
		0b01111000,
		0b00001100,
		0b11001100,
		0b01111000
		},{
		0b00000000,//T
		0b11111100,
		0b10110100,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b00110000
		},{
		0b00000000,//U
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b01111100
		},{
		0b00000000,//V
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b11001100,
		0b01111000,
		0b00110000
		},{
		0b00000000,//W
		0b11000110,
		0b11000110,
		0b11000110,
		0b11010110,
		0b11111110,
		0b11101110,
		0b11000110
		},{
		0b00000000,//X
		0b11000110,
		0b11000110,
		0b01101100,
		0b00111000,
		0b01101100,
		0b11000110,
		0b11000110
		},{
		0b00000000,//Y
		0b11001100,
		0b11001100,
		0b11001100,
		0b01111000,
		0b00110000,
		0b00110000,
		0b00110000
		},{
		0b00000000,//Z
		0b11111100,
		0b00001100,
		0b00011000,
		0b00110000,
		0b01100000,
		0b11000000,
		0b11111100
		},{
		0b00000000,//0
		0b01111000,
		0b11001100,
		0b11011100,
		0b11101100,
		0b11001100,
		0b11001100,
		0b01111000
		},{
		0b00000000,//1
		0b00110000,
		0b00110000,
		0b01110000,
		0b00110000,
		0b00110000,
		0b00110000,
		0b11111100
		},{
		0b00000000,//2
		0b01111000,
		0b11001100,
		0b00001100,
		0b00011000,
		0b01100000,
		0b11000000,
		0b11111100
		},{
		0b00000000,//3
		0b01111000,
		0b11001100,
		0b00001100,
		0b00111000,
		0b00001100,
		0b11001100,
		0b01111000
		},{
		0b00000000,//4
		0b00011000,
		0b00111000,
		0b01011000,
		0b10011000,
		0b11111100,
		0b00011000,
		0b00011000
		},{
		0b00000000,//5
		0b11111100,
		0b11000000,
		0b11111000,
		0b00001100,
		0b00001100,
		0b11001100,
		0b01111000
		},{
		0b00000000,//6
		0b01111000,
		0b11001100,
		0b11000000,
		0b11111000,
		0b11001100,
		0b11001100,
		0b01111000
		},{
		0b00000000,//7
		0b11111100,
		0b11001100,
		0b00011000,
		0b00011000,
		0b00110000,
		0b00110000,
		0b00110000
		},{
		0b00000000,//8
		0b01111000,
		0b11001100,
		0b11001100,
		0b01111000,
		0b11001100,
		0b11001100,
		0b01111000
		},{
		0b00000000,//9
		0b01111000,
		0b11001100,
		0b11001100,
		0b01111100,
		0b00001100,
		0b11001100,
		0b01111000
		},{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
		}};


const int IMAGES_LEN = sizeof(IMAGES)/8;
int imageIndex = 0;


int byteArray[300];
int byteIndex=0;


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

// Clears the whole 8x8 matrix
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

// Fills the whole 8x8 matrix 
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

// Commands for initializing the 8x8 matrix
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

// Test method to draw pixels on a cetrain row.
void drawPixel(int row, int data)
{
	twi_start();
	twi_tx(0xE0);
	twi_tx(row*2);
	twi_tx(data);
	twi_stop();
}

// Reverses a byte eg. 0b11110000 becomes 0b00001111
int reverse(int byte)
{
	
	byte = (byte * 0x0202020202ULL & 0x010884422010ULL) % 1023;
	return byte;

}


// Used for drawing elements of IMAGES[]
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

// print all chars and numbers on the 8x8 display
void testAlphabet()
{
	for(int i = 0; i<36; i++)
	{
		drawArray(IMAGES[i]);
		wait(1000);
	}
}

// Draws on the 8x8 matrix
void scrollVertical(int byteArray[], int index)
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

// adds an character to the byte array.
void addChar(int character)
{
	for(int i =0; i<8;i++)
	{
		byteArray[byteIndex] = IMAGES[character][i];
		byteIndex++;
	}

	
}

// adds an empty row to the byte array.
void addSpace()
{
	byteArray[byteIndex] = 0b00000000;
	byteIndex++;
}


// Adds all the characters to the byte array.
void addText(int characters[])
{
	int i = 0;

	while(characters[i] != -1)
	{
		addChar(characters[i]);
		addSpace();
		i++;
	}
}


int main( void )
{
	
	twi_init();		// Init TWI interface
	initcommands();	// Standard commands before running 
	clear();
	
	int i = 0;

	int string[] = {charK,charA,charN,charK,charA, charN, charO,charO,charK,charN,charI,charE,charT, -1}; // -1 is the stop index which indicates the end of the array
	addText(string);

	while (1)
	{
		// Draws the right dots on the 8x8 dot matrix
		scrollVertical(byteArray,i);
		i++;

		// resets i when end of the string is reached
		if(i >= byteIndex)
			i = 0;

		wait(200);
	}

	return 1;
}