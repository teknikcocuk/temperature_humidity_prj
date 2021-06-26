#ifndef __USR_SYSTEM_H
#define __USR_SYSTEM_H

#include "usr_timer.h"
#include "dht11.h"
#include "menu_manager.h"
#include "ssd1306.h"
#include "fonts.h"
#include "flash.h"

extern uint8_t g_exti4_15_it;

void usr_system_init(void);

void usr_system_general(void);

void usr_all_read_func(void);

#endif