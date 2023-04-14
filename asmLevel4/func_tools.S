.global Init
.global off
.global prtDgt
.global prtTime

.extern dgt
.extern curr_dig

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

    ldi  r18,  0b00111111
    out  DDRB, r18

    cli
    
    clr  r18
    sts  TCCR2A, r18
    ldi  r18,  0b00000100
    sts  TCCR2B, r18

    ldi  r18,  0b00000001
    sts  TIMSK2, r18

    sei

    ldi  r18, 0b11111000
    sts  digits +  0, r18
    ldi  r18, 0b00111101
    sts  digits +  1, r18
    ldi  r18, 0b00110000
    sts  digits +  2, r18
    ldi  r18, 0b00111100
    sts  digits +  3, r18
    ldi  r18, 0b11011000
    sts  digits +  4, r18
    ldi  r18, 0b00111110
    sts  digits +  5, r18
    ldi  r18, 0b01111000
    sts  digits +  6, r18
    ldi  r18, 0b00111110
    sts  digits +  7, r18
    ldi  r18, 0b00110000
    sts  digits +  8, r18
    ldi  r18, 0b00111111
    sts  digits +  9, r18
    ldi  r18, 0b01101000
    sts  digits + 10, r18
    ldi  r18, 0b00111111
    sts  digits + 11, r18
    ldi  r18, 0b11101000
    sts  digits + 12, r18
    ldi  r18, 0b00111111
    sts  digits + 13, r18
    ldi  r18, 0b00111000
    sts  digits + 14, r18
    ldi  r18, 0b00111100
    sts  digits + 15, r18
    ldi  r18, 0b11111000
    sts  digits + 16, r18
    ldi  r18, 0b00111111
    sts  digits + 17, r18
    ldi  r18, 0b01111000
    sts  digits + 18, r18
    ldi  r18, 0b00111111
    sts  digits + 19, r18

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
;   destroys r24, r20, r20, r28, Z
;-----------------------------
prtDgt:
    lsl  r24
    ldi  r20, 0b00000100        ;mask

    L1:
    cpi  r22, 0
    breq L2

    lsl  r20
    dec  r22
    rjmp L1
    L2:

    clr  r31
    mov  r30, r24

    subi r30, lo8(-(digits))
    sbci r31, hi8(-(digits))

    com  r20

    ldd  r18, Z + 1
    and  r18, r20
    
    out  PORTB, r18

    ld   r18, Z
    out  PORTD, r18

    ret





vRam:   .byte   4

digits: .byte   20
