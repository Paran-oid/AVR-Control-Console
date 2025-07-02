#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "input.h"
#include "output.h"
#include "timer.h"
#include "usart.h"
#include "utils.h"

volatile uint8_t debounce_active = 0;
volatile uint8_t debounce_counter = 0;
volatile uint8_t button_pressed = 0;

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

int main(void) {
    uint8_t option = 0;
    uint8_t res = 0;

    usart_init();
    adc_init(POT);

    timer0_init();
    button0_init();
    sei();

    while (1) {
        if (!button_pressed) {
            output_terminal(&option);
        } else {
            res = option_handle(option, &button_pressed);
            usart_clear();
            if (res != 0) error_handler();

            // option 0 uses PWM on timer0 so we have to reinitialize timer0
            if (option == 0) {
                timer0_init();
            }

            button_pressed = 0;
            option = 0;
        }
    }

    return 0;
}