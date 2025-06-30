#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "input.h"
#include "output.h"
#include "usart.h"

int main(void) {
    usart_init();
    adc_init();

    while (1) {
        output_terminal();
    }
    return 0;
}