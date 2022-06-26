
EXTERN CODE:NEAR (TIMER0_INTERRUPT)
	
;=============================================================  

TIMER_INTERRUPT_ENTRANCE SEGMENT CODE AT 00Bh
RSEG TIMER_INTERRUPT_ENTRANCE
    LJMP TIMER_0_INT

;=============================================================  
INTERRUPT_HANDLER SEGMENT CODE
RSEG INTERRUPT_HANDLER

    TIMER_0_INT:
		;Save program state
        PUSH    ACC
        PUSH    B
        PUSH	DPH 
        PUSH	DPL 
        PUSH	PSW
        PUSH	0x00
        PUSH	0x01
        PUSH	0x02
        PUSH	0x03
        PUSH	0x04
        PUSH	0x05
        PUSH	0x06
        PUSH    0x07

        CALL TIMER0_INTERRUPT

        ;Restore program state
        POP     0x07
        POP     0x06
        POP     0x05
        POP     0x04
        POP     0x03
        POP     0x02
        POP     0x01
        POP     0x00
        POP     PSW
        POP     DPL
        POP     DPH
        POP     B
        POP     ACC
        RETI

;=============================================================  
END