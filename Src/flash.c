#include "usr_general.h"

float m_flash_data[2] = {SET_VAL_INIT, HYS_VAL_INIT};

uint32_t flash_write_data(uint32_t start_page_adress, uint32_t *data, uint16_t number_of_words)
{
    FLASH_EraseInitTypeDef erase_init_struct;
    uint32_t page_error = 0;
    uint16_t cnt_word = 0;

    erase_init_struct.TypeErase   = FLASH_TYPEERASE_PAGES;
	erase_init_struct.PageAddress = start_page_adress;
	erase_init_struct.NbPages     = 1;

    HAL_FLASH_Unlock();

    if (HAL_FLASHEx_Erase(&erase_init_struct, &page_error) != HAL_OK)
    {
        return HAL_FLASH_GetError();
	}

    while (cnt_word < number_of_words)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, start_page_adress, data[cnt_word]) == HAL_OK)
	     {
	    	 start_page_adress += 4;  
	    	 ++cnt_word;
	     }
	     else
	     {
	    	 return HAL_FLASH_GetError();
	     }
	   }

    HAL_FLASH_Lock();
    return HAL_OK;
}

void flash_read_data(uint32_t start_page_adress, uint32_t *rx_buf, uint16_t number_of_words)
{
    while (1)
	{
		*rx_buf = *(uint32_t *)start_page_adress;
		start_page_adress += 4;
		rx_buf++;
		if (!(--number_of_words)) break;
	}
}

void float_to_bytes(uint8_t *ftoa_bytes_temp, float float_var)
{
    union{
      float a;
      uint8_t bytes[4];
    }thing;

    thing.a = float_var;

    for (uint8_t i = 0; i < 4; i++) {
      ftoa_bytes_temp[i] = thing.bytes[i];
    }
}

float bytes_to_float(uint8_t *ftoa_bytes_temp)
{
	union{
      float a;
      uint8_t bytes[4];
    }thing;

    for (uint8_t i = 0; i < 4; i++) {
    	thing.bytes[i] = ftoa_bytes_temp[i];
    }

    float float_variable = thing.a;
    return float_variable;
}

void flash_write_num(uint32_t start_page_adress, float *data)
{
	uint8_t bytes_of_array[8];
	uint8_t bytes_of_array_element[4];
	uint8_t i = 0, j = 0, k = 0;

	for(i = 0; i < 2; i++)
	{
		float_to_bytes(bytes_of_array_element, data[i]);

		for(j = 0; j < 4; j++)
		{
			bytes_of_array[k] = bytes_of_array_element[j];
			++k;
		}
	}

	flash_write_data (start_page_adress, (uint32_t *)bytes_of_array, 2);
}

float flash_read_num(uint32_t start_page_adress)
{
	uint8_t buffer[4];
	float value;

	flash_read_data(start_page_adress, (uint32_t *)buffer, 1);
	value = bytes_to_float(buffer);
	return value;
}

float flash_read_set_val()
{
    return flash_read_num((uint32_t)SET_VAL_ADRESS);
}

float flash_read_hys_val()
{
    return flash_read_num((uint32_t)HYS_VAL_ADRESS);
}

void flash_write_set_val(float num)
{
	m_flash_data[SET_VAL_INDX] = num;
	flash_write_num((uint32_t)PAGE63_START_ADRESS, m_flash_data);
}

void flash_write_hys_val(float num)
{
	m_flash_data[HYS_VAL_INDX] = num;
	flash_write_num((uint32_t)PAGE63_START_ADRESS, m_flash_data);
}






