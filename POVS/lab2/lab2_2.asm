#include "p16f84.inc"

counter equ 0x0c
array_begin set 0x20
eeprom_begin set 0x0
array_size set 0x5

goto begin

write_eeprom:
	movlw eeprom_begin
	movwf EEADR
	movlw array_begin
	movwf FSR
	movlw array_size
	movwf counter
write_loop:
	movf INDF, 0
	movwf EEDATA

	bsf STATUS, RP0
	bcf	INTCON, GIE
	bsf EECON1, WREN
	movlw 0x55
	movwf EECON2
	movlw 0xAA
	movwf EECON2
	bsf EECON1, WR
	bsf INTCON, GIE
write_wait:
	btfsc EECON1, WR
	goto write_wait
	bcf STATUS, RP0
	
	incf FSR, 1
	incf EEADR, 1
	decfsz counter, 1
	goto write_loop
	return

begin:
	movlw array_begin
	movwf FSR
	movlw array_size
	movwf counter
	
write_array_loop:
	movf counter, 0
	sublw array_size
	movwf INDF
	incf FSR, 1
	decfsz counter, 1
	goto write_array_loop
	call write_eeprom
	end