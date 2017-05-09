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
	lds yh, $04
	ldi yl, $00
	ldd r14, Y+0
	ldd r15, Y+1
	ldd r12, Y+2
	ldd r13, Y+3
	ldd r10, Y+4
	ldd r11, Y+5
	ldd r8, Y+6
	ldd r9, Y+7
				; stap 1
	mov r4, r10
	add r4, r15
				; stap 2
	mov r5, r11
	adc r5, r14

	mov r6, r8
	adc r6, r12

	mov r7, r13
	adc r7, r9

	std Y+4, r4 ; Resultaat opslaan
	std Y+5, r5 
	std Y+6, r6 
	std Y+7, r7 


no_end: ; unlimited loop, when done
	rjmp no_end
	


