#ifndef __MENU_MANAGER_H
#define __MENU_MANAGER_H

#define MENU_NUM 4
#define BUTTON_NUM 4
#define HOME_PAGE 0
#define MENU1 1
#define MENU1_1 2
#define MENU1_2 3
#define UP 0
#define DOWN 1
#define OK 2
#define CANCEL 3
#define ALARM_DELAY 100
#define SET_VAL_INDX 0
#define HYS_VAL_INDX 1
#define SET_VAL_INIT 28
#define HYS_VAL_INIT 1

extern uint8_t g_which_menu, g_which_button;

extern void (*display_menu[MENU_NUM])(void);
extern void (*menu_button[MENU_NUM][BUTTON_NUM])(void);

void display_init(void);

void display_home_page(void);

void display_menu1(void);

void display_menu1_1(void);

void display_menu1_2(void);

void home_page_up(void);

void home_page_down(void);

void home_page_ok(void);

void home_page_cancel(void);

void menu1_up(void);

void menu1_down(void);

void menu1_ok(void);

void menu1_cancel(void);

void menu1_1_up(void);

void menu1_1_down(void);

void menu1_1_ok(void);

void menu1_1_cancel(void);

void menu1_2_up(void);

void menu1_2_down(void);

void menu1_2_ok(void);

void menu1_2_cancel(void);

void hold_button_menu1_1(void);

void hold_button_menu1_2(void);

#endif
