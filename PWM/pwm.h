#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

#define SERVO PB1

#define SERVO_MAX 5500UL
#define SERVO_MID 3500UL
#define SERVO_MIN 1500UL

void pwm0_init(void);
void pwm0_destroy(void);

void pwm1_servo_init(void);
void pwm1_servo_destroy(void);

int8_t led_dim(volatile uint8_t* button_pressed);
int8_t servo_control(volatile uint8_t* button_pressed);

#endif