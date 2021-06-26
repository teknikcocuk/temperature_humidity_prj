#include "usr_general.h"

static float s_flash_data[2] = {SET_VAL_INIT, HYS_VAL_INIT};
float watch_set_val = 0;
float watch_hys_val = 0;

void usr_system_init(void)
{
    HAL_Delay(500);
    HAL_TIM_Base_Start_IT(&htim6);
    HAL_TIM_Base_Start(&htim15);
    HAL_RTC_Init(&hrtc);
    display_init();

    flash_write_data((uint32_t)PAGE63_START_ADRESS, (uint32_t *)s_flash_data, 2U);
}

void usr_system_general(void)
{
    if(g_tim6_cnt1 > 1500)
    {
        usr_all_read_func();
        g_tim6_cnt1 = 0;
    }

    if(g_tim6_cnt2 > 100)
    {
        display_menu[g_which_menu]();

        watch_set_val = flash_read_set_val();
        watch_hys_val = flash_read_hys_val();

        g_tim6_cnt2 = 0;
    }
}

void usr_all_read_func(void)
{
    dht11_read();
    read_date_time();
}