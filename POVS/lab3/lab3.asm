#include "p16f84.inc"
 
vcycle set 0xFF
vpause equ 0x0c

button_current equ 0x0a
button_old equ 0x0b
curr_status equ 0x0f

number_times set 0x3
counter equ 0x0d

CLRF button_current
CLRF button_old
CLRF curr_status
GOTO begin

org 4
halt: goto halt

WAIT_1S:
	MOVLW vcycle
	MOVWF vpause
	L0:
	DECFSZ vpause
	GOTO L0
	MOVLW vcycle
	MOVWF vpause
	L1:
	DECFSZ vpause
	GOTO L1
	RETURN

INIT_PORTB:
	BCF STATUS,RP0
	CLRF PORTB
	BSF STATUS,RP0
	MOVLW 0x00
	MOVWF TRISB
	BSF TRISB, 4
	BCF STATUS,RP0
	RETURN

FIRST:
	BCF STATUS,RP0
	FIRST_LOOP:
	BSF PORTB, 0
	BSF PORTB, 1
	BSF PORTB, 2
	BSF PORTB, 7
	CALL WAIT_1S
	BCF PORTB, 1
	BCF PORTB, 2
	BCF PORTB, 7
	BCF PORTB, 0
	CALL WAIT_1S
	RETURN

SECOND:
	BCF STATUS,RP0
	BCF STATUS,RP0

	BSF PORTB, 0x0
	CALL WAIT_1S
	BCF PORTB, 0x0

	BSF PORTB, 0x1
	CALL WAIT_1S
	BCF PORTB, 0x1

	BSF PORTB, 0x2
	CALL WAIT_1S
	BCF PORTB, 0x2

	BSF PORTB, 0x7
	CALL WAIT_1S
	BCF PORTB, 0x7
	RETURN

BUTTON_STATUS:
	BTFSC PORTB, 3
	RETLW 0
	RETLW 1

begin:
	CALL INIT_PORTB
	BCF INTCON, GIE
MAIN_LOOP:
	CALL BUTTON_STATUS
	MOVWF button_current
	
	SUBWF button_old, 0
	btfsc STATUS,Z
	GOTO SKIP
	MOVF button_current, 0
	MOVWF curr_status

SKIP:
	MOVF button_current, 0
	MOVWF button_old
	btfsc curr_status, 8
	GOTO SECOND_CALL
	CALL FIRST
	
	GOTO MAIN_LOOP
SECOND_CALL:
	CALL SECOND
	GOTO MAIN_LOOP

	END