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
	lds R17, $60
	com R17
	STS $60, R17
end
	rjmp end


