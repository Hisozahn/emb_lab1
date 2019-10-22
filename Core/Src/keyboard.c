#include "keyboard.h"
#include "i2c.h"

#define KEYBOARD_ROW_NUM	4
#define KEYBOARD_COL_NUM	3

int keyboard_key_is_in_set(keyboard_key key, const keyboard_key_set *key_set)
{
	keyboard_key_set test = 1U << key;

	return (test & *key_set);
}

static int keyboard_Read(keyboard_key_set *key_set)
{
	uint8_t read_data;
	uint8_t write_data;
	uint8_t row;
	keyboard_key_set set = 0;
	HAL_StatusTypeDef rc;
	int i;

	for (i = 0; i < KEYBOARD_ROW_NUM; i++)
	{
		write_data = (~(1U << i)) & 0x0f;
		rc = HAL_I2C_Mem_Write(&hi2c1,KEYBOARD_I2C_ADDR,0x01,1,&write_data,1,10);
		if (rc == HAL_OK)
			rc = HAL_I2C_Mem_Read(&hi2c1,KEYBOARD_I2C_ADDR,0x00,1,&read_data,1,10);

		if (rc != HAL_OK)
			return 1;

		row = (~(read_data >> 4)) & 0x07;

		set |= (keyboard_key_set)row << (KEYBOARD_COL_NUM * i);
	}

	*key_set = set;

	return 0;
}

uint8_t keyboard_Init(void)
{
	HAL_StatusTypeDef rc;
	uint8_t write_data = 0xf0;
	HAL_Delay(100);
	rc = HAL_I2C_Mem_Write(&hi2c1,KEYBOARD_I2C_ADDR,0x03,1,&write_data,1,10);

	return (rc == HAL_OK ? 0 : 1);
}

int keyboard_Get(keyboard_key_set *data)
{
	return keyboard_Read(data);
}
