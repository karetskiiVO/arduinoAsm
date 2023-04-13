.global Init
.global off
.global prtDgt

.equ DDRB  , 0x04
.equ PORTB , 0x05
.equ DDRD  , 0x0a
.equ PORTD , 0x0b
.equ TCCR2A, 0xb0
.equ TCCR2B, 0xb1
.equ TIMSK2, 0x70

;-----------------------------
;   destroys r18
;-----------------------------
Init:
    ldi  r18, 0b11111000
    andi r18, 0b11111110
    out DDRD, r18

    ldi r18,  0b00111111
    out DDRB, r18

    cli
    
    clr r18
    sts TCCR2A, r18
    ldi r18,  0b00000100
    sts TCCR2B, r18

    ldi r18,  0b00000001
    sts TIMSK2, r18

    sei

    ret
;-----------------------------
;   destroys r18
;-----------------------------
off:
    clr r18
    out PORTD, r18
    ldi r18, 0b00111100
    out PORTB, r18

    ret
;-----------------------------
;   input    r24, r22
;   destroys r18, r20, r20, Z
;-----------------------------
prtDgt:
    ; compute displ
        cpi  r22, 0
        breq dgt0

        cpi  r22, 1
        breq dgt1

        cpi  r22, 2
        breq dgt2

        cpi  r22, 3
        breq dgt3

    bk0:

    ; compute digit
        cpi  r24, 0
        breq prt0

        cpi  r24, 1
        breq prt1

        cpi  r24, 2
        breq prt2

        cpi  r24, 3
        breq prt3

        cpi  r24, 4
        breq prt4

        cpi  r24, 5
        breq prt5

        cpi  r24, 6
        breq prt6

        cpi  r24, 7
        breq prt7

        cpi  r24, 8
        breq prt8

        cpi  r24, 9
        breq prt9
    bk1:

    and  r18, r20
    
    out  PORTB, r18
    out  PORTD, r16

    ret

prt0:
    ldi r16, 0b11111000
    ldi r18, 0b00111101
    rjmp bk1

prt1:
    ldi r16, 0b00110000
    ldi r18, 0b00111100
    rjmp bk1

prt2:
    ldi r16, 0b11011000
    ldi r18, 0b00111110
    rjmp bk1

prt3:
    ldi r16, 0b01111000
    ldi r18, 0b00111110
    rjmp bk1

prt4:
    ldi r16, 0b00110000
    ldi r18, 0b00111111
    rjmp bk1

prt5:
    ldi r16, 0b01101000
    ldi r18, 0b00111111
    rjmp bk1

prt6:
    ldi r16, 0b11101000
    ldi r18, 0b00111111
    rjmp bk1

prt7:
    ldi r16, 0b00111000
    ldi r18, 0b00111100
    rjmp bk1

prt8:
    ldi r16, 0b11111000
    ldi r18, 0b00111111
    rjmp bk1

prt9:
    ldi r16, 0b01111000
    ldi r18, 0b00111111
    rjmp bk1
 
dgt0:
    ldi  r20, 0b11111011
    rjmp bk0
dgt1:
    ldi  r20, 0b11110111
    rjmp bk0
dgt2:
    ldi  r20, 0b11101111
    rjmp bk0
dgt3:
    ldi  r20, 0b11011111
    rjmp bk0