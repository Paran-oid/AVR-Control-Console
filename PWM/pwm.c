#include "pwm.h"

#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "usart.h"

void pwm0_init(void) {
    DDRD |= (1 << DDD6);

    // Fast PWM mode, non inverting on OC0A
    TCCR0A |= (1 << COM0A1);
    // PWM mode
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    OCR0A = 0;

    // Start timer with prescaler 64
    TCCR0B |= (1 << CS01) | (1 << CS00);
}

void pwm0_destroy(void) {
    TCCR0A = 0;
    TCCR0B = 0;

    DDRD &= ~(1 << DDD6);
    OCR0A = 0;
}

int8_t led_dim(volatile uint8_t* button_pressed) {
    *button_pressed = 0;  // reset so we can use it later
    pwm0_init();

    usart_clear();
    print_string("=== LED Diming ===\r\n");
    print_string("Control brightness of led with POT\r\n");
    print_string("(Press the button to quit)\r\n");

    uint16_t pot_val = 0;
    uint8_t pwm_val = 0;
    while (1) {
        if (*button_pressed) {
            break;
        }

        pot_val = adc_read(PC0);

        pwm_val = pot_val >> 2;
        OCR0A = pwm_val;

        _delay_ms(10);
    }
    pwm0_destroy();

    return 0;
}