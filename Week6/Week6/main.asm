;
; Week6.asm
;
; Created: 3/16/2017 6:18:01 PM
; Author : RMSjoshua
;


; Replace with your application code
.INCLUDE "m128def.inc"
;
.CSEG
.ORG $0000
rjmp main
;
.CSEG
.ORG $0200
;
main:
; initialisatie data geheugen
;

ldi R17, $55 ; waarde register 17 op hex 55
STS $540, R17 ; kopieren waarde register 17 naar adres 540 tot 548
STS $541, R17
STS $542, R17
STS $543, R17
STS $544, R17
STS $545, R17
STS $546, R17
STS $547, R17
STS $548, R17


no_end: ; unlimited loop, when done
rjmp no_end
.DSEG
.ORG $0400
a: .BYTE 2
b: .BYTE 2
c: .BYTE 2