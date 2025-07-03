#include "sleep.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "adc.h"
#include "timer.h"
#include "usart.h"

void sleep_init(uint8_t mode) {
    set_sleep_mode(mode);
    sleep_enable();
}
void sleep_destroy(void) {
    sleep_disable();
    set_sleep_mode(SLEEP_MODE_IDLE);
}

int8_t sleep_mode_exec(volatile uint8_t* button_pressed) {
    *button_pressed = 0;  // reset so we can use it later

    usart_clear();
    print_string("=== Sleep Mode ===\r\n");
    print_string("Control current sleep mode with POT\r\n");
    print_string("(Press the button to select)\r\n");
    print_string("Current mode: Idle");

    char* modes[] = {"Idle", "ADC Noise Reduction", "Power Save", "Power Down"};
    uint8_t modes_vals[] = {SLEEP_MODE_IDLE, SLEEP_MODE_ADC,
                            SLEEP_MODE_PWR_SAVE, SLEEP_MODE_PWR_DOWN};

    uint16_t pot_val = 0;
    uint8_t option_previous = 0xff;
    uint8_t option_selected;
    while (!*button_pressed) {
        pot_val = adc_read(PC0);
        option_selected = pot_val * 3 / 1024;

        if (option_selected > 3) option_selected = 3;

        if (option_selected != option_previous) {
            usart_clear();
            print_string("=== Sleep Mode ===\r\n");
            print_string("Control current sleep mode with POT\r\n");
            print_string("(Press the button to quit)\r\n");
            print_string("Current Mode:");
            print_string(modes[option_selected]);
            print_string("\r\n");

            sleep_destroy();
            sleep_init(modes_vals[option_selected]);

            option_previous = option_selected;
        }
    }

    *button_pressed = 0;  // now we are in sleep mode

    print_string("Applied!\r\n");
    print_string(
        "you can modify macro in timer.h for WAKEUP_SECONDS to make it take "
        "less time!\r\n");
    wdt_interrupt_init();
    wdt_counter = 0;
    while (wdt_counter < WAKEUP_SECONDS) {
        sleep_mode();
    }
    wdt_interrupt_destroy();
    sleep_destroy();

    return 0;
}