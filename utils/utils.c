
#include "utils.h"

#include <avr/interrupt.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "adc.h"
#include "input.h"
#include "usart.h"

void error_handler(void) {
    usart_destroy();
    adc_destroy();
    button0_destroy();
    cli();

    while (1);
}
void swap(void* a, void* b, size_t elsize) {
    uint8_t temp[elsize];
    memcpy(temp, a, elsize);
    memcpy(a, b, elsize);
    memcpy(b, temp, elsize);
}
