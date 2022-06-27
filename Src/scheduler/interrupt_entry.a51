
EXTERN CODE:NEAR (TIMER0_INTERRUPT, __RESCHEDULE)

EXTERN DATA (FLAG_NOSCHED, __TMP_INTFRAME)

SBIT ET0 = 0xA8 ^ 1
	
;=============================================================  

TIMER_INTERRUPT_ENTRANCE SEGMENT CODE AT 00Bh
RSEG TIMER_INTERRUPT_ENTRANCE
    LJMP TIMER_0_INT

;=============================================================  
INTERRUPT_HANDLER SEGMENT CODE
RSEG INTERRUPT_HANDLER

    PUBLIC TIMER_0_INT
    TIMER_0_INT:
		
        ;Save program state, PC already saved by hardware
        ;Size of interrupt frame is 15 bytes
        
        ;PUSH   PC_LOW
        ;PUSH   PC_HIGH
        POP __TMP_INTFRAME+1
        POP __TMP_INTFRAME

        MOV __TMP_INTFRAME+2, ACC
        MOV __TMP_INTFRAME+3, B
        MOV __TMP_INTFRAME+4, DPH
        MOV __TMP_INTFRAME+5, DPL
        MOV __TMP_INTFRAME+6, PSW

        MOV __TMP_INTFRAME+7, R0
        MOV __TMP_INTFRAME+8, R1
        MOV __TMP_INTFRAME+9, R2
        MOV __TMP_INTFRAME+10, R3
        MOV __TMP_INTFRAME+11, R4
        MOV __TMP_INTFRAME+12, R5
        MOV __TMP_INTFRAME+13, R6
        MOV __TMP_INTFRAME+14, R7

        MOV __TMP_INTFRAME+15, SP

        CALL TIMER0_INTERRUPT

        ;Restore program state
        MOV ACC , __TMP_INTFRAME+2
        MOV B   ,  __TMP_INTFRAME+3
        MOV DPH , __TMP_INTFRAME+4
        MOV DPL , __TMP_INTFRAME+5
        MOV PSW , __TMP_INTFRAME+6

        MOV R0  , __TMP_INTFRAME+7
        MOV R1  , __TMP_INTFRAME+8
        MOV R2  , __TMP_INTFRAME+9
        MOV R3  , __TMP_INTFRAME+10
        MOV R4  , __TMP_INTFRAME+11
        MOV R5  , __TMP_INTFRAME+12
        MOV R6  , __TMP_INTFRAME+13
        MOV R7  , __TMP_INTFRAME+14

        MOV SP  , __TMP_INTFRAME+15

        PUSH __TMP_INTFRAME
        PUSH __TMP_INTFRAME+1

        RETI

;============================================================= 
    PUBLIC __YIELD
    __YIELD:
        CLR ET0

        ;Save program state, PC already saved by hardware
        ;Size of interrupt frame is 15 bytes
        
        ;PUSH   PC_LOW
        ;PUSH   PC_HIGH
        POP __TMP_INTFRAME+1
        POP __TMP_INTFRAME

        MOV __TMP_INTFRAME+2, ACC
        MOV __TMP_INTFRAME+3, B
        MOV __TMP_INTFRAME+4, DPH
        MOV __TMP_INTFRAME+5, DPL
        MOV __TMP_INTFRAME+6, PSW

        MOV __TMP_INTFRAME+7, R0
        MOV __TMP_INTFRAME+8, R1
        MOV __TMP_INTFRAME+9, R2
        MOV __TMP_INTFRAME+10, R3
        MOV __TMP_INTFRAME+11, R4
        MOV __TMP_INTFRAME+12, R5
        MOV __TMP_INTFRAME+13, R6
        MOV __TMP_INTFRAME+14, R7

        MOV __TMP_INTFRAME+15, SP

        CALL __RESCHEDULE

        ;Restore program state
        MOV ACC , __TMP_INTFRAME+2
        MOV B   ,  __TMP_INTFRAME+3
        MOV DPH , __TMP_INTFRAME+4
        MOV DPL , __TMP_INTFRAME+5
        MOV PSW , __TMP_INTFRAME+6

        MOV R0  , __TMP_INTFRAME+7
        MOV R1  , __TMP_INTFRAME+8
        MOV R2  , __TMP_INTFRAME+9
        MOV R3  , __TMP_INTFRAME+10
        MOV R4  , __TMP_INTFRAME+11
        MOV R5  , __TMP_INTFRAME+12
        MOV R6  , __TMP_INTFRAME+13
        MOV R7  , __TMP_INTFRAME+14

        MOV SP  , __TMP_INTFRAME+15

        PUSH __TMP_INTFRAME
        PUSH __TMP_INTFRAME+1

        SETB ET0
        RET

END