#ifndef INPUT_H
#define INPUT_H

#include <avr/io.h>

// confirm button
void button0_init(void);
void button0_destroy(void);

uint8_t option_receive(void);
int8_t option_handle(uint8_t option, volatile uint8_t* button_pressed);

#endif