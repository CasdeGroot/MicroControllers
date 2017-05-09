;
; Week6.asm
;
; Created: 3/16/2017 6:18:01 PM
; Author : RMSjoshua
;


; Replace with your application code
.INCLUDE "m128def.inc"

main:
; initialisatie data geheugen
;
start:
	lds R16, 10
	ldi xh, $66
	ldi xl, 00
	ldi yh, $8B
	ldi yl, 00

loop: 
	ld R17, X+
	ST Y+, R17
	dec R16
	brne loop

end:
	rjmp end


