#include "usr_general.h"

float m_temp_set_val = 0, m_temp_hys_val = 0;
uint8_t m_hys_state = 0;
uint8_t m_is_alarm_nonactive = 1;
uint8_t m_menu1_line_cnt = 0;
uint8_t g_which_menu = 0, g_which_button = 0;
uint8_t m_cnt_set_up = 0;
uint8_t m_cnt_set_down = 0;
uint8_t m_cnt_hys_up = 0;
uint8_t m_cnt_hys_down = 0;
char* m_alarm_str = "ALARM";
char* m_cursor_str = ">";
char* m_clear_cursor_str = " ";
char* m_clear_line_str = "     ";
char m_set_val_str[16] = " ";
char m_hys_val_str[16] = " ";
char m_menu1_1_str[16] = " ";
char m_menu1_2_str[16] = " ";

void (*display_menu[MENU_NUM])(void) = {display_home_page, display_menu1, display_menu1_1, display_menu1_2};
void (*menu_button[MENU_NUM][BUTTON_NUM])(void) = {{home_page_up, home_page_down, home_page_ok, home_page_cancel},
                                                   {menu1_up, menu1_down, menu1_ok, menu1_cancel},
                                                   {menu1_1_up, menu1_1_down, menu1_1_ok, menu1_1_cancel},
                                                   {menu1_2_up, menu1_2_down, menu1_2_ok, menu1_2_cancel}};

void display_init(void)
{
    SSD1306_Init(); 
    SSD1306_Fill(0);
    SSD1306_UpdateScreen();
}

void display_home_page(void)
{
    g_which_menu = HOME_PAGE;

    SSD1306_Fill(0);
 
    SSD1306_GotoXY(25,5);
    SSD1306_Puts(g_temp_hum_str, &Font_7x10, 1);

    if((g_temp_val > flash_read_set_val() + flash_read_hys_val()) || m_hys_state)
    {
        m_hys_state = 1;
        if(m_is_alarm_nonactive)
        {
            SSD1306_GotoXY(46,22);
            SSD1306_Puts(m_clear_line_str, &Font_7x10, 1); 
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
            m_is_alarm_nonactive = 0;
        }
        else
        {
            SSD1306_GotoXY(46,22);
            SSD1306_Puts(m_alarm_str, &Font_7x10, 1);
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
            m_is_alarm_nonactive = 1;
        }
    }

    if(g_temp_val < flash_read_set_val() - flash_read_hys_val())
    {
        m_hys_state = 0;
        SSD1306_GotoXY(46,22);
        SSD1306_Puts(m_clear_line_str, &Font_7x10, 1);
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
    } 

    SSD1306_GotoXY(46,39);
    SSD1306_Puts(g_time, &Font_7x10, 1);
    SSD1306_GotoXY(36,49);
    SSD1306_Puts(g_date, &Font_7x10, 1);

    SSD1306_UpdateScreen();
}

void display_menu1(void)
{
    g_which_menu = MENU1;

    sprintf(m_set_val_str, "set_val = %.1f", flash_read_set_val());
    sprintf(m_hys_val_str, "hys_val = %.1f", flash_read_hys_val());

    SSD1306_Fill(0);

    SSD1306_GotoXY(7, 5);
    SSD1306_Puts(m_set_val_str, &Font_7x10, 1);
    SSD1306_GotoXY(7,15);
    SSD1306_Puts(m_hys_val_str, &Font_7x10, 1);

    if(m_menu1_line_cnt == 0)
    {
        SSD1306_GotoXY(0, 5);
        SSD1306_Puts(m_cursor_str, &Font_7x10, 1);
        SSD1306_GotoXY(0, 15);
        SSD1306_Puts(m_clear_cursor_str, &Font_7x10, 1);
    }

    else
    {
        SSD1306_GotoXY(0, 15);
        SSD1306_Puts(m_cursor_str, &Font_7x10, 1);
        SSD1306_GotoXY(0, 5);
        SSD1306_Puts(m_clear_cursor_str, &Font_7x10, 1);
    }

    SSD1306_UpdateScreen();
}

void display_menu1_1(void)
{
    g_which_menu = MENU1_1;

    hold_button_menu1_1();

    sprintf(m_menu1_1_str, "set_val = %.1f", m_temp_set_val);
    
    SSD1306_Fill(0);

    SSD1306_GotoXY(7, 5);
    SSD1306_Puts(m_menu1_1_str, &Font_7x10, 1);

    SSD1306_UpdateScreen();
}

void display_menu1_2(void)
{
    g_which_menu = MENU1_2;

    hold_button_menu1_2();

    sprintf(m_menu1_2_str, "hys_val = %.1f", m_temp_hys_val);

    SSD1306_Fill(0);

    SSD1306_GotoXY(7, 5);
    SSD1306_Puts(m_menu1_2_str, &Font_7x10, 1);

    SSD1306_UpdateScreen();
}

void home_page_up(void)
{

}

void home_page_down(void)
{

}

void home_page_ok(void)
{
    g_which_menu = MENU1;
}

void home_page_cancel(void)
{

}

void menu1_up(void)
{
    switch (m_menu1_line_cnt)
    {
        case 0:
        m_menu1_line_cnt = 1;
            break;

        case 1:
        m_menu1_line_cnt = 0;
            break;
    }
}

void menu1_down(void)
{
    switch (m_menu1_line_cnt)
    {
        case 0:
        m_menu1_line_cnt = 1;
            break;

        case 1:
        m_menu1_line_cnt = 0;
            break;
    }
}

void menu1_ok(void)
{
    switch (m_menu1_line_cnt)
    {
    case 0:
    m_temp_set_val = flash_read_set_val();
    g_which_menu = MENU1_1;
        break;
    
    case 1:
    m_temp_hys_val = flash_read_hys_val();
    g_which_menu = MENU1_2;
        break;
    }
}

void menu1_cancel(void)
{
    g_which_menu = HOME_PAGE;
}

void menu1_1_up(void)
{
    if(m_temp_set_val < 50)
    {
        m_temp_set_val += 0.1f;
        if(m_temp_set_val > 50) m_temp_set_val = 50; 
    }
}

void menu1_1_down(void)
{
    if(m_temp_set_val > 0)
    {
        m_temp_set_val -= 0.1f;
        if(m_temp_set_val < 0) m_temp_set_val = 0;
    }
}

void menu1_1_ok(void)
{
    flash_write_set_val(m_temp_set_val);
}

void menu1_1_cancel(void)
{
    m_cnt_set_up = 0;
    m_cnt_set_down = 0;
    g_which_menu = MENU1;
}

void menu1_2_up(void)
{
    if(m_temp_hys_val < 5)
    {
        m_temp_hys_val += 0.1f;
        if(m_temp_hys_val > 5) m_temp_hys_val = 5;
    }
}

void menu1_2_down(void)
{
    if(m_temp_hys_val > 1)
    {
        m_temp_hys_val -= 0.1f;
        if(m_temp_hys_val < 1) m_temp_hys_val = 1;
    }
}

void menu1_2_ok(void)
{
    flash_write_hys_val(m_temp_hys_val);
}

void menu1_2_cancel(void)
{
    m_cnt_hys_up = 0;
    m_cnt_hys_down = 0;
    g_which_menu = MENU1;
}

void hold_button_menu1_1(void)
{
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))
    {
        ++m_cnt_set_up;
        if(m_cnt_set_up == 5)
        {
            m_cnt_set_up = 0;
            if(m_temp_set_val < 50) m_temp_set_val += 0.1f;
        }

    }
    else 
    {
        m_cnt_set_up = 0;
    }

    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))
    {
        ++m_cnt_set_down;
        if(m_cnt_set_down == 5)
        {
            m_cnt_set_down = 0;
            if(m_temp_set_val > 0)  m_temp_set_val -= 0.1f;
        }
    }
    else 
    {
        m_cnt_set_down = 0;
    }
}

void hold_button_menu1_2(void)
{
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))
    {
        ++m_cnt_hys_up;
        if(m_cnt_hys_up == 5)
        {
            m_cnt_hys_up = 0;
            if(m_temp_hys_val < 5)  m_temp_hys_val += 0.1f;
        }
    }
    else 
    {
        m_cnt_hys_up = 0;
    }

    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))
    {
        ++m_cnt_hys_down;
        if(m_cnt_hys_down == 5)
        {
            m_cnt_hys_down = 0;
            if(m_temp_hys_val > 0) m_temp_hys_val -= 0.1f;
        }
    }
    else 
    {
        m_cnt_hys_down = 0;
    }
}
