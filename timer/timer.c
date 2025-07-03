#include "timer.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "adc.h"
#include "usart.h"

ISR(INT0_vect) {
    if (!debounce_active) {
        button_pressed = 1;
        debounce_active = 1;
        debounce_counter = DEBOUNCE_TIME_MS;
    }
}

ISR(TIMER0_COMPA_vect) {
    if (debounce_active) {
        if (--debounce_counter == 0) {
            debounce_active = 0;
        }
    }
}

ISR(WDT_vect) { wdt_counter++; }

void timer0_init(void) {
    TCCR0A |= (1 << WGM01);  // CTC mode
    OCR0A = 249;             // 249 for 1ms
    TIMSK0 |= (1 << OCIE0A);
    TCCR0B |= (1 << CS00) | (1 << CS01);
}
void timer0_destroy(void) {
    TCCR0A = 0;
    TCCR0B = 0;
    TIMSK0 = 0;
}

void wdt_interrupt_init(void) {
    cli();

    WDTCSR = (1 << WDCE) | (1 << WDE);                 // enable watch dog timer
    WDTCSR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1);  // Interrupt every ~1s
    sei();
}

void wdt_interrupt_destroy(void) {
    cli();
    WDTCSR = (1 << WDCE) | (1 << WDE);
    WDTCSR = 0x00;
    sei();
}

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
    DDRD |= (1 << DDD6);
    timer1_init();
    OCR1A = 15625;

    usart_clear();
    print_string("=== LED blinking ===\r\n");
    print_string("Control blinking speed with POT(max 4 seconds)\r\n");
    print_string("(Press the button to quit)\r\n");

    uint16_t pot_val = 0;
    uint16_t previous_pot_val = 0;
    while (1) {
        if (*button_pressed) {
            break;
        }
        pot_val = adc_read(PC0);
        pot_val >>= 2;
        uint16_t milliseconds = (uint16_t)((uint32_t)pot_val * 4000 / 255);
        // avoid float divison cuz on AVR it's so slow
        uint16_t calculated = (uint16_t)((uint32_t)milliseconds * 1000 / 64);
        if (abs(pot_val - previous_pot_val) > DIFF_TOLERANCE) {
            OCR1A = calculated;
            TCNT1 = 0;
            previous_pot_val = pot_val;
        }
    }
    timer1_destroy();
    return 0;
}