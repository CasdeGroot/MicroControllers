/*
 * Counter.c
 *
 * Created: 2/23/2017 11:46:50 AM
 *  Author: RMSjoshua
 */ 

  #define F_CPU 8000000

  #include "LCD.h"
  #include <avr/io.h>
  #include <util/delay.h>
  #include <avr/interrupt.h>
  #include <stdio.h>

  int ocr_count = 0;

  void timer2_init(void);

  ISR(TIMER2_COMP_vect)
  {
	ocr_count++;
	if(ocr_count == 15)
	{
	 PORTD = 0b10000000;	 
	}
	
	if (ocr_count == 40)
	{
		PORTD = 0b00000000;
		ocr_count = 0;
	}
	 
  }

  void timer2_init(void)
  {
	OCR2 = 250*1;
	TIMSK = 0b10000000;
	sei();
	TCCR2 = 0b00001101; //counting via PD7 prescaling 1024
  }

  int main(void)
  {
	  init_4bit_mode();

	  DDRC = 0xFF;
	  timer2_init();


	  DDRD = 0x00; //PD7 op input
	  DDRB = 0xFF;

	  
	  while(1)
	  {
		_delay_ms(10);
	  }
	  
	  return 1;
  }