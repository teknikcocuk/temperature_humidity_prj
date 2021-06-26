#include "usr_general.h"

char g_time[16] = " ";
char g_date[16] = " ";
uint16_t g_tim6_cnt1 = 0;
uint16_t g_tim6_cnt2 = 0;
uint8_t g_tim6_flag = 0;
RTC_TimeTypeDef m_time;
RTC_DateTypeDef m_date;

void delay_us(uint16_t delay)
{
  uint16_t init_time = (uint16_t)__HAL_TIM_SET_COUNTER(&htim15, 0);
  while((uint16_t)__HAL_TIM_GET_COUNTER(&htim15) - init_time < delay);
}

void read_date_time(void)
{
  for(int i=0 ;i < 16; i++) g_time[i] = '\0';
  for(int i=0 ;i < 16; i++) g_date[i] = '\0';

  HAL_RTC_GetTime(&hrtc, &m_time, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &m_date, RTC_FORMAT_BIN);

  sprintf(g_time, "%0.2d:%0.2d", m_time.Hours, m_time.Minutes);
  sprintf(g_date, "%0.2d.%0.2d.%0.2d", m_date.Date, m_date.Month, m_date.Year);
}