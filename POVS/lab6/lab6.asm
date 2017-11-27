#include p16f84a.inc

set_value equ 0x0f

org 0x0
goto main

check_value_1:
   movlw 0x01
   btfsc PORTB, 4
   movwf set_value
   
   movlw 0x04
   btfsc PORTB, 5
   movwf set_value
   
   movlw 0x07
   btfsc PORTB, 6
   movwf set_value
   
   movlw 0x0A
   btfsc PORTB, 7
   movwf set_value
   
   return

check_value_2:
   movlw 0x02
   btfsc PORTB, 4
   movwf set_value
   
   movlw 0x05
   btfsc PORTB, 5
   movwf set_value
   
   movlw 0x08
   btfsc PORTB, 6
   movwf set_value
   
   movlw 0x00
   btfsc PORTB, 7
   movwf set_value
   
   return
   
check_value_3:
   movlw 0x03
   btfsc PORTB, 4
   movwf set_value
   
   movlw 0x06
   btfsc PORTB, 5
   movwf set_value
   
   movlw 0x09
   btfsc PORTB, 6
   movwf set_value
   
   movlw 0x0B
   btfsc PORTB, 7
   movwf set_value
   
   return

display:
   movf set_value, 0
   movwf PORTA
   return

init_port_a:
   clrf PORTA
   bsf STATUS, RP0   
   movlw 0x0
   movwf TRISA
   bcf STATUS, RP0
   return
   
init_port_b:
   clrf PORTB
   bsf STATUS, RP0
   movlw 0xf0
   movwf TRISB
   bcf STATUS, RP0
   return

main:
   call init_port_a
   call init_port_b
loop:
   movlw 0x01
   movwf PORTB
   call check_value_1
   
   movlw 0x02
   movwf PORTB
   call check_value_2
   
   movlw 0x04
   movwf PORTB
   call check_value_3
   call display
   goto loop
   end
