#ifndef __FLASH_H
#define __FLASH_H

#define PAGE63_START_ADRESS 0x0800FC00U
#define SET_VAL_ADRESS PAGE63_START_ADRESS
#define HYS_VAL_ADRESS (PAGE63_START_ADRESS + 4)

uint32_t flash_write_data(uint32_t start_page_adress, uint32_t *data, uint16_t number_of_words);

void flash_read_data(uint32_t start_page_adress, uint32_t *rx_buf, uint16_t number_of_words);

void float_to_bytes(uint8_t *ftoa_bytes_temp, float float_var);

float bytes_to_float(uint8_t *ftoa_bytes_temp);

// void flash_write_num(uint32_t start_page_adress, float num);

void flash_write_num(uint32_t start_page_adress, float *data);

float flash_read_num(uint32_t start_page_adress);

float flash_read_set_val();

float flash_read_hys_val();

void flash_write_set_val(float num);

void flash_write_hys_val(float num);

#endif