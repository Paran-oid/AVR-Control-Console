#include "output.h"

#include <util/delay.h>

#include "input.h"
#include "usart.h"

int output_terminal(void) {
    uint8_t picked = handle_option();

    const char* arr_str[] = {"=== AVR Multi Control Station ===",
                             "1) Set LED Brightness",
                             "2) Blink LED",
                             "3) Servo Control",
                             "4) Read Analog Voltage",
                             "5) Sleep Mode"};
    uint8_t arr_str_size = 5;

    uint8_t was_colored = 0;
    for (uint8_t i = 0; i < arr_str_size; i++) {
        if (i != 0 && i == picked) {
            // TODO: make the highlight work just like in vue project init in
            // example
            print_string("\033[31m");
            was_colored = 1;
        }

        print_string(arr_str[i]);

        if (was_colored) {
            print_string("\033[0m");
        }

        print_string("\r\n");
    }

    print_string("Current Option: ");
    transmit_byte(picked + '0');
    print_string("\r\n");

    return 0;
}