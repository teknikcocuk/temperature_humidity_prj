#ifndef __DHT11_H
#define __DHT11_H

#define OUTPUT 1
#define INPUT 0

extern uint16_t g_temp_val, g_hum_val;
extern char g_temp_hum_str[16];

void set_gpio_mode(uint8_t);

uint8_t dht11_read(void);

#endif