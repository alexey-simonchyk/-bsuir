#include "p16f84.inc" 

counter equ 0x0c
array_begin set 0x20
array_size set 0x5
eeprom_shift set 0x0

org 0x2100
de 0x42
de 0x53
de 0x55
de 0x49
de 0x52
org 0x0

read_data:
	MOVLW array_size
	MOVWF counter
	MOVLW eeprom_shift
	MOVWF EEADR
	MOVLW array_begin
	MOVWF FSR
read:
	BSF STATUS, RP0
	BSF EECON1, RD
	BCF STATUS, RP0
	MOVF EEDATA, 0
	MOVWF INDF
	INCF FSR, 1
	INCF EEADR, 1
	DECFSZ counter, 1
	GOTO read
	RETURN

begin:
	CALL read_data
	NOP
	END