/*
 * Timer.c
 *
 * Created: 2/23/2017 11:21:59 AM
 *  Author: RMSjoshua
 */ 
 #define F_CPU 8000000

 #include "LCD.h"
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include <stdio.h>


 //int main(void)
 //{
	//DDRD = 0xFF;
	//init_4bit_mode();
//
	//DDRD = 0x00; //PD7 op input
	//DDRB = 0xFF;
	//TCCR2 = 0b00000111; //counting via PD7 rising edge
//
	//char str[16];
	//
	//while(1)
	//{
		//sprintf(str, "%d", TCNT2);
		//write_string_lcd(str);
		//_delay_ms(500);
	//}
	//
	//
	//return 1;
//}