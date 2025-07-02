#include "input.h"

#include <avr/interrupt.h>

#include "adc.h"
#include "pwm.h"
#include "timer.h"
#include "usart.h"

void button0_init(void) {
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PD2);

    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);
}
void button0_destroy(void) {
    DDRD &= ~(1 << DDD2);
    PORTD &= ~(1 << PD2);

    EICRA = 0;
    EIMSK = 0;
}

uint8_t option_receive(void) {
    uint16_t pot_val = adc_read(POT);

    uint8_t option = (pot_val * 5) / 1024 + 1;
    if (option > 5) option = 5;

    // we don't want to get 0 returned
    return option;
}

int8_t option_handle(uint8_t option, volatile uint8_t* button_pressed) {
    switch (option) {
        case 1:
            return led_dim(button_pressed);
        case 2:
            return led_blink(button_pressed);
        case 3:
            return servo_control(button_pressed);
        case 4:
            return analog_voltage_read(button_pressed);
        default:
            break;
    }
    return 0;
}