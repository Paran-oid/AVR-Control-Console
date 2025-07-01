#include "output.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "input.h"
#include "usart.h"

int output_terminal(uint8_t* picked_option) {
    uint8_t currently_picked = option_receive();

    if (currently_picked != *picked_option) {
        usart_clear();
        const char* arr_str[] = {"=== AVR Multi Control Station ===",
                                 "1) Set LED Brightness",
                                 "2) Blink LED",
                                 "3) Servo Control",
                                 "4) Read Analog Voltage",
                                 "5) Sleep Mode"};
        uint8_t arr_str_size = 6;

        uint8_t was_colored = 0;
        for (uint8_t i = 0; i < arr_str_size; i++) {
            if (i != 0 && i == currently_picked) {
                print_string("\033[31m");
                was_colored = 1;
            }

            print_string(arr_str[i]);

            if (was_colored) {
                // make sure to not color the rest lines
                print_string("\033[0m");
            }

            print_string("\r\n");
        }

        print_string("Current Option: ");
        transmit_byte(currently_picked + '0');
        print_string("\r\n");

        *picked_option = currently_picked;
        _delay_ms(300);
    }

    return 0;
}
