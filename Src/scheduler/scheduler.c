#include "scheduler.h"
#include "../display/seg_led.h"
#include "../mem/mem.h"

XDATA u8 interrupt_frames[8][15];
XDATA u8 current_process = 0;
XDATA u32 system_cycles = 0;
XDATA u8 process_slot = 1;

XDATA u8 remaining_timeslices = DEFAULT_TIMESLICES;
XDATA u8 proc_time_share[8] = {
    DEFAULT_TIMESLICES, DEFAULT_TIMESLICES,
    DEFAULT_TIMESLICES, DEFAULT_TIMESLICES,
    DEFAULT_TIMESLICES, DEFAULT_TIMESLICES,
    DEFAULT_TIMESLICES, DEFAULT_TIMESLICES
};//This determines the number of timeslices assigned when each process is scheduled

//Only processes with 0 sleep countdown can be scheduled
XDATA u16 proc_sleep_countdown[8] ={0, 0, 0, 0, 0, 0, 0, 0};

DATA u8 flag_nosched = 0;

void start_scheduler(u8 ms_per_interrupt)
{
    //Set Timer0, Enable interrupt.
    {   
        XDATA TIM_InitTypeDef timer_settings;
        timer_settings.TIM_Mode = TIM_16BitAutoReload;
        timer_settings.TIM_Polity = PolityHigh;
        timer_settings.TIM_Interrupt = ENABLE;
        timer_settings.TIM_ClkSource = TIM_CLOCK_12T;
        timer_settings.TIM_ClkOut = DISABLE;
        timer_settings.TIM_Value = calc_TIM_from_ms_12t(ms_per_interrupt*2);
        timer_settings.TIM_Run = ENABLE;
        Timer_Inilize(Timer0, &timer_settings);
    }

    //Enable interrupts
    EA = 1;
}

DATA u8 tmp_save_sp;
void timer0_interrupt()
{
    system_cycles++;
    remaining_timeslices--;
    decrement_sleep_counters();

    //Running atomic code, do not reschedule
    if(flag_nosched) return;

    //Current process has remaining time slices, do not reschedule
    if(remaining_timeslices) return;
//=============================================================================

    //Save interrupt frame of current process
    tmp_save_sp = SP;
    my_memcpy(interrupt_frames[current_process], (u8 IDATA*)(tmp_save_sp-16), 15);
    //=========================================================================

    current_process = select_process();
    remaining_timeslices = proc_time_share[current_process];

    /*
    //Debug
    led_display_content = system_cycles>>4;
    DISP_LED();
    */
    
    //=========================================================================
    //Load interrupt frame of current process
    my_memcpy((u8 IDATA*)(tmp_save_sp-16), interrupt_frames[current_process], 15);
}

u8 select_process()
{
    XDATA u8 tmp_process;
    tmp_process = current_process;

    //sequentially check other processes
    while((tmp_process = NEXT(tmp_process)) != current_process)
        if(process_ready(tmp_process))
            return tmp_process;

    //if no other process can run, check if current process can run again
    if (process_ready(current_process))
        return current_process;
    
    //Can't find a process to run, Error code 1.
    error_spin(1);
}

u8 process_ready(u8 pid)
{
    //Check process exists
    if(!PROC_EXISTS(pid))
        return 0;

    //Check process is not sleeping
    if(proc_sleep_countdown[pid])
        return 0;

    return 1;
}

u8 __start_process(PROCESS_ENTRY entry)
{
    XDATA u8 tmp_process;
    
    //find a slot for new process
    tmp_process = find_empty_slot();
    
    //create interrupt frame for process
    memzero(interrupt_frames[tmp_process], 15);
    interrupt_frames[tmp_process][INTFRM_ADDRLO] = ((u16)entry) & 0xff;
    interrupt_frames[tmp_process][INTFRM_ADDRHI] = (((u16)entry)>>8) & 0xff;

    //flag process existence
    process_slot |= BIT(tmp_process);

    return tmp_process;
}

u8 find_empty_slot()
{
    XDATA u8 tmp_process;

    for(tmp_process = 0; tmp_process<8; tmp_process++)
    {
        if(!PROC_EXISTS(tmp_process))
        {
            tmp_process |= BIT(7); //set this bit to indicate that a valid slot is found
            break;
        }
    }

    //can't find a slot for new process
    if(!(tmp_process&BIT(7)))
        error_spin(2);

    return (tmp_process & 0x07); //remove the flag before returning
}

void decrement_sleep_counters()
{
    COUNTDOWN(proc_sleep_countdown[0]);
    COUNTDOWN(proc_sleep_countdown[1]);
    COUNTDOWN(proc_sleep_countdown[2]);
    COUNTDOWN(proc_sleep_countdown[3]);
    COUNTDOWN(proc_sleep_countdown[4]);
    COUNTDOWN(proc_sleep_countdown[5]);
    COUNTDOWN(proc_sleep_countdown[6]);
    COUNTDOWN(proc_sleep_countdown[7]);
    
    LEDs &= 0xC0; //clear low 6 bits    
    LEDs |= proc_sleep_countdown[1] >> 8; //Show sleep counter of process1 on 0-2 bits
    LEDs |= (proc_sleep_countdown[0] >> 4) & (0x38); //Show sleep counter of process0 on 3-5 bits
}

//process code -> __yield(asm) -> __reschedule -> return to __yield -> return to new context
void __reschedule()
{
    DATA u8 tmp_save_sp;

    tmp_save_sp = SP;
    my_memcpy(interrupt_frames[current_process], (u8 IDATA*)(tmp_save_sp-16), 15);

    current_process = select_process();
    remaining_timeslices = proc_time_share[current_process];

    my_memcpy((u8 IDATA*)(tmp_save_sp-16), interrupt_frames[current_process], 15);
}

u8 expected = 1;
void tmp_errcheck()
{
    return;
    expected = !expected;
    if ((!expected) && (LEDs&0x80))
        error_spin(21);
    else if (expected && (!(LEDs&0x80)))
        error_spin(20);
    

    if (proc_sleep_countdown[1]) error_spin(11);
    if (proc_sleep_countdown[2]) error_spin(12);
    if (proc_sleep_countdown[3]) error_spin(13);
    if (proc_sleep_countdown[4]) error_spin(14);
    if (proc_sleep_countdown[5]) error_spin(15);
    if (proc_sleep_countdown[6]) error_spin(16);
    if (proc_sleep_countdown[7]) error_spin(17);
}

XDATA u8 tmp_curr_seg;
void error_spin(u8 errorcode)
{
    //disable interrupts (spin forever)
    TR0 = 0;

    seg_set_str("ERROR   ");

    seg_display_content[7]=seg_decoder[errorcode%10];
    errorcode/=10;
    seg_display_content[6]=seg_decoder[errorcode%10];
    errorcode/=10;
    seg_display_content[5]=seg_decoder[errorcode%10];
    errorcode/=10;

    while (1)
    {
        tmp_curr_seg++;
        DISP_SEG(tmp_curr_seg & 0x7);
        delay_ms(2);
    }
}