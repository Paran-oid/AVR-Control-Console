#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

void pwm0_init(void);
void pwm0_destroy(void);

int8_t led_dim(volatile uint8_t* button_pressed);

#endif