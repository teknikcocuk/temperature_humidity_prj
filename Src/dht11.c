#include "usr_general.h"

char g_temp_hum_str[16] = " ";

uint16_t g_temp_val = 0, g_hum_val=0;
uint64_t m_data = 0;
uint16_t m_time1 = 0, m_time2 = 0;
uint16_t m_bit = 0;
uint16_t  m_parity = 0;

uint8_t dht11_read(void)
{
    m_data = 0; m_time1 = 0, m_time2 = 0, g_temp_val=0, g_hum_val=0, m_parity = 0,  m_bit = 0;

	//start communication
	set_gpio_mode(OUTPUT);			//set pin direction as input
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_RESET);		
	HAL_Delay(20);					//wait 20 ms in Low state 
	set_gpio_mode(INPUT);			//set pin direction as input

	//check dht answer
	__HAL_TIM_SET_COUNTER(&htim15, 0);			//set timer counter to zero
	while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_SET) if((uint16_t)__HAL_TIM_GET_COUNTER(&htim15) > 500) return 0;
	__HAL_TIM_SET_COUNTER(&htim15, 0);
	while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_RESET) if((uint16_t)__HAL_TIM_GET_COUNTER(&htim15) > 500) return 0;
	m_time1 = (uint16_t)__HAL_TIM_GET_COUNTER(&htim15);
	__HAL_TIM_SET_COUNTER(&htim15, 0);
	while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_SET) if((uint16_t)__HAL_TIM_GET_COUNTER(&htim15) > 500) return 0;
	m_time2 = (uint16_t)__HAL_TIM_GET_COUNTER(&htim15);
 
	//if answer is wrong return
	if(m_time1 < 75 && m_time1 > 85 && m_time2 < 75 && m_time2 > 85)
	{
		return 0;
	}

	for(int j = 0; j < 40; j++)
	{
		__HAL_TIM_SET_COUNTER(&htim15, 0);
		while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_RESET) if((uint16_t)__HAL_TIM_GET_COUNTER(&htim15) > 500) return 0;
		__HAL_TIM_SET_COUNTER(&htim15, 0);
		while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == GPIO_PIN_SET) if((uint16_t)__HAL_TIM_GET_COUNTER(&htim15) > 500) return 0;
		m_time1 = (uint16_t)__HAL_TIM_GET_COUNTER(&htim15);
 
		if(m_time1 > 20 && m_time1 < 30) //if pass time 25uS set as LOW
		{
			m_bit = 0;
		}
		else if(m_time1 > 60 && m_time1 < 80) //if pass time 70 uS set as HIGH
		{
			m_bit = 1;
		}
 
		//set i th data in data buffer
		m_data |= m_bit;
		m_data <<= 1;
	}
	m_data >>= 1;

	g_hum_val = (m_data & 0xff00000000) >> 32;
	g_temp_val = (m_data & 0xff0000) >> 16;
	m_parity = (m_data & 0xff);

	for(int i = 0; i < 16; i++) g_temp_hum_str[i] = '0';
	sprintf(g_temp_hum_str, "t=%d   h=%d", g_temp_val, g_hum_val);

	return 1;
}

void set_gpio_mode(uint8_t pMode)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	if(pMode == OUTPUT)
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	}
	else 
	{
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	}

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}



