#include "p16f84.inc" 

c_start set 0x30
v_current_i equ 0x0F
v_current_j equ 0x0D
v_next equ 0x0C
v_swap equ 0x0E
c_num set 0xA
c_num_j equ 0x0A
c_num_i equ 0x0B

BEGIN:
	BCF STATUS, 0x5
	CLRF v_current_i
	CLRF v_current_j
	CLRF v_next
	CLRF v_swap

	MOVLW c_num-1
	MOVWF c_num_i

	MOVLW c_num-2
	MOVWF c_num_j
LOOP1:
	CLRF v_current_j
LOOP2:
	MOVF v_current_j, 0
	SUBWF c_num_j, 0
	BTFSS STATUS, C
	GOTO END_LOOP2

	MOVF v_current_j, 0
	ADDLW c_start
	MOVWF FSR
	MOVF INDF, 0
	MOVWF v_swap
	
	INCF FSR
	MOVF INDF, 0
	MOVWF v_next
	MOVF v_swap, 0
	SUBWF v_next, 0
	BTFSC STATUS, C
	GOTO SWAP
	GOTO SKIP

SWAP:
	MOVF v_swap, 0
	MOVWF INDF
	MOVF v_next, 0
	DECF FSR
	MOVWF INDF
	
SKIP:
	INCF v_current_j, F
	GOTO LOOP2
END_LOOP2:
	INCF v_current_i, F
	MOVF c_num_i, 0
	SUBWF v_current_i, 0
	BTFSS STATUS, C
	GOTO LOOP1

	end