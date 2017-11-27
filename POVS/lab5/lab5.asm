#include p16f84a.inc

number_steps set 0x7
loop_i equ 0x0a
buffer equ 0x0b

org 0x0
goto begin

init_ports:
   movlw 0x3
   movwf PORTA
   clrf PORTB
   
   bsf STATUS, RP0
   clrf TRISA
   bsf TRISA, 2
   clrf TRISB
   bcf STATUS, RP0
   return

begin:
   call init_ports
main_loop:
   movlw number_steps
   movwf loop_i
   clrf buffer
   
   bcf PORTA, 0
   bsf PORTA, 0
   bcf PORTA, 2
   bcf PORTA, 3
   
   btfsc PORTA, 2
   goto second_element
first_element:
   bsf PORTA, 3
   goto read_loop
second_element
   bsf PORTA, 4
   
read_loop:
   bcf PORTA, 1
   bsf PORTA, 1
   
   rlf buffer
   btfsc PORTA, 2
   bsf buffer, 0
   
   decfsz loop_i, 1
   goto read_loop
   
   movf buffer, 0
   movwf PORTB
   goto main_loop
   end