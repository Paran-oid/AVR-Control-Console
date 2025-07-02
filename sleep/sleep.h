#ifndef SLEEP_H
#define SLEEP_H

#include <avr/io.h>

void sleep_init(uint8_t mode);
void sleep_destroy(void);

int8_t sleep_mode_exec(volatile uint8_t* button_pressed);

#endif