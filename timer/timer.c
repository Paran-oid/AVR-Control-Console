#include "timer.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "usart.h"

void timer1_init(void) {
    TCCR1B |= (1 << WGM12);  // CTC Mode
    TIMSK1 |= (1 << OCIE1A);
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

void timer1_destroy(void) {
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
}

ISR(TIMER1_COMPA_vect) { PORTD ^= (1 << PD6); }

uint8_t led_blink(volatile uint8_t* button_pressed) {
    *button_pressed = 0;  // reset so we can use it later
    timer1_init();
    DDRD |= (1 << DDD6);
    OCR1A = 15625;

    usart_clear();
    print_string("=== LED blinking ===\r\n");
    print_string("Control blinking speed with POT(max 4 seconds)\r\n");
    print_string("(Press the button to quit)\r\n");

    uint16_t pot_val = 0;
    while (1) {
        if (*button_pressed) {
            break;
        }

        pot_val = adc_read(PC0);
        pot_val >>= 2;

        uint16_t mapped_value = (uint16_t)((uint32_t)pot_val * 4000 / 255);

        // equivalent to: miliseconds / 0.064
        // but since we want to avoid float division at
        // all cost we do miliseocnds * 125 / 8
        OCR1A = (mapped_value * 125) / 8;

        if (OCR1A < 10) OCR1A = 10;
    }
    timer1_destroy();

    return 0;
}