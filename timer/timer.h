#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

#define DIFF_TOLERANCE 5
#define DEBOUNCE_TIME_MS 100

void timer0_init(void);
void timer0_destroy(void);

void timer1_init(void);
void timer1_destroy(void);
uint8_t led_blink(volatile uint8_t *button_pressed);

#endif