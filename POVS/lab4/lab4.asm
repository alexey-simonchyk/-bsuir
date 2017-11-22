#include p16f84a.inc
   
   led_status equ 0x0c
   display_number equ 0x0a
   w_temp equ 0x0b
   status_temp equ 0x0d
   current_number equ 0x0f

   org 0x0
   goto main
   
   org 0x4
   goto i_handler
   
org 0x10
   
main:
   bcf STATUS, RP0
   clrf PORTB
   bsf STATUS, RP0
   movlw 0x01
   movwf TRISB
   bcf STATUS, RP0
   
   clrf INTCON
   clrf current_number
   bsf INTCON, INTE
   bsf INTCON, GIE
   
loop:
   nop
   goto loop


i_handler:
  
   movwf w_temp
   swapf STATUS, W
   movwf status_temp
   
   call change_led_status
   call increment_number
   
   swapf status_temp, W
   movwf STATUS
   swapf w_temp, F
   swapf w_temp, W
   
   
   bcf INTCON, INTF
   bsf INTCON, GIE
   
   return

increment_number:
   incf current_number, 1
   movlw 0x0A
   subwf current_number, w
   btfsc STATUS, Z
   clrf current_number
   call set_number
   return

set_number:
   btfsc current_number, 0
   bsf PORTB, 1
   btfss current_number, 0
   bcf PORTB, 1
   
   btfsc current_number, 1
   bsf PORTB, 2
   btfss current_number, 1
   bcf PORTB, 2
   
   btfsc current_number, 2
   bsf PORTB, 3
   btfss current_number, 2
   bcf PORTB, 3
   
   btfsc current_number, 3
   bsf PORTB, 4
   btfss current_number, 3
   bcf PORTB, 4
   
   return
   
change_led_status:
   movf  0x0, w
   subwf led_status, w
   btfsc STATUS, Z
   goto enable_led
   goto disable_led
   sleep
   return

enable_led:
   bsf led_status, 0
   bcf STATUS,RP0
   bsf PORTB, 0x5
   return

disable_led:
   clrf led_status
   bcf STATUS,RP0
   bcf PORTB, 0x5
   return
   
   end