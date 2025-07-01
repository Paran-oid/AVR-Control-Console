#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void timer1_init(void);
void timer1_destroy(void);
uint8_t led_blink(volatile uint8_t *button_pressed);

#endif