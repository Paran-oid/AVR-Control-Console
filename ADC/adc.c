#include "adc.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <util/delay.h>

#include "usart.h"

volatile uint8_t adc_ready_flag = 0;

void adc_init(uint8_t channel) {
    ADMUX = (1 << REFS0) | (channel & 0x0F);

    ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    ADCSRA |= (1 << ADEN);
}

void adc_destroy(void) {
    ADMUX = 0;
    ADCSRA = 0;
}

void adc_sleep_mode_init(void) {
    set_sleep_mode(SLEEP_MODE_ADC);
    ADCSRA |= (1 << ADIE);
}
void adc_sleep_mode_destroy(void) {
    ADCSRA &= ~(1 << ADIE);
    set_sleep_mode(SLEEP_MODE_IDLE);
}

ISR(ADC_vect) { adc_ready_flag = 1; }

uint16_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));
    return ADC;
}

static uint16_t oversample16x(void) {
    uint16_t total = 0;
    for (uint8_t i = 0; i < 16; i++) {
        adc_ready_flag = 0;

        ADCSRA |= (1 << ADSC);
        sleep_mode();

        while (!adc_ready_flag);

        total += ADC;
    }
    return total >> 2;
}

int8_t analog_voltage_read(volatile uint8_t* button_pressed) {
    adc_destroy();  // make sure pot doesn't affect read voltage

    adc_init(VOLTMETER);
    adc_sleep_mode_init();

    *button_pressed = 0;  // reset so we can use it later
    DDRB &= ~(1 << HOLD_BUTTON);
    PORTB |= (1 << HOLD_BUTTON);

    usart_clear();
    print_string("=== Read Analog Voltage ===\r\n");
    print_string(
        "Add the desires voltage to the provided cable and connect other to "
        "GND\r\n");
    print_string("Make sure you modify the macros to your need\r\n");
    print_string(
        "hold the hold button to your right to display new measurements\r\n");
    print_string("(Press the button to quit)\r\n");

    uint8_t instructions_printed = 1;

    while (1) {
        if (*button_pressed) {
            break;
        }

        uint8_t button_state = !(PINB & (1 << HOLD_BUTTON));  // pressed if 0
        if (button_state) {
            while (!(PINB & (1 << HOLD_BUTTON))) {
                float voltage =
                    oversample16x() * REF_VCC * VOLTAGE_DIV_FACTOR / 4096;
                print_float(voltage);
                print_string("\r\n");
                instructions_printed = 0;

                _delay_ms(300);
            }
        } else {
            if (!instructions_printed) {
                usart_clear();
                print_string("=== Read Analog Voltage ===\r\n");
                print_string(
                    "Add the desires voltage to the provided cable and connect "
                    "other to "
                    "GND\r\n");
                print_string(
                    "Make sure you modify the macros to your need\r\n");
                print_string("hold the button to confirm new measurements\r\n");
                print_string("(Press the button to quit)\r\n");
                instructions_printed = 1;
            }
        }
        _delay_ms(500);
    }
    adc_sleep_mode_destroy();
    adc_destroy();  // get rid of voltmeter pin

    adc_init(POT);  // reenable POT

    return 0;
}