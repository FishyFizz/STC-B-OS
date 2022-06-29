#ifndef _TEST_PROCESS_H_
#define _TEST_PROCESS_H_

#include "../global.h"
#include "../scheduler/scheduler.h"
#include "../display/seg_led.h"
#include "../conc/semaphore.h"
#include "../bit_ops/bit_ops.h"
#include "../events/events.h"
#include "../rs485/rs485.h"
#include "../error/error.h"
#include "../random/random.h"
#include "../mem/mem.h"
#include "../ds1302/ds1302.h"
#include "../buzzer/buzzer.h"
#include "../usbcom/usbcom.h"
#include "../music/music.h"

void rtc_test();
void music_doudizhu();
void music_monsterhunter();
void kill_test();
void sleep_test();
void semaphore_test();
void rs485_test();
void usbcom_test();

#endif