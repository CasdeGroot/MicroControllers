;
; Week6.asm
;
; Created: 3/16/2017 6:18:01 PM
; Author : RMSjoshua
;


; Replace with your application code
.INCLUDE "m128def.inc"

main:

start:
	ldi R16, 0
	ldi R17, 7
	out PORTA, R16

loop:
	inc R16
	out PORTA, R16
	dec R17
	brne loop

back:
	ldi R17, 7

secondloop:
	dec R16
	out PORTA, R16
	dec R17
	brne secondloop

end:
	rjmp start