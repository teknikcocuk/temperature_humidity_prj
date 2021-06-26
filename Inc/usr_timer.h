#ifndef __USR_TIMER_H
#define __USR_TIMER_H

extern char g_time[16];
extern char g_date[16];
extern uint16_t g_tim6_cnt1;
extern uint16_t g_tim6_cnt2;
extern uint8_t g_tim6_flag;

void delay_us(uint16_t delay);

void read_date_time(void);

#endif