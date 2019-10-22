#include "stm32f4xx_hal.h"
#include "fonts.h"

#ifndef __KEYBOARD_H
#define __KEYBOARD_H

// I2c port as defined in main generated by CubeMx
#define KEYBOARD_I2C_PORT		hi2c1
// I2c address
#define KEYBOARD_I2C_ADDR        0xE2


//	Definition of the i2c port in main
extern I2C_HandleTypeDef KEYBOARD_I2C_PORT;

typedef uint16_t keyboard_key_set;

typedef enum keyboard_key {
	KEYBOARD_KEY_0 = 0,
	KEYBOARD_KEY_1,
	KEYBOARD_KEY_2,
	KEYBOARD_KEY_3,
	KEYBOARD_KEY_4,
	KEYBOARD_KEY_5,
	KEYBOARD_KEY_6,
	KEYBOARD_KEY_7,
	KEYBOARD_KEY_8,
	KEYBOARD_KEY_9,
	KEYBOARD_KEY_10,
	KEYBOARD_KEY_11,
} keyboard_key;
//
//  Function definitions
//
uint8_t keyboard_Init(void);
int keyboard_Get(keyboard_key_set *key_set);
int keyboard_key_is_in_set(keyboard_key key, const keyboard_key_set *key_set);

#endif	/* __KEYBOARD_H */
