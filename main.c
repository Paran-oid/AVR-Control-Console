#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "input.h"
#include "output.h"
#include "timer.h"
#include "usart.h"
#include "utils.h"

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

            timer0_init();

            button_pressed = 0;
            option = 0;
        }
    }

    return 0;
}