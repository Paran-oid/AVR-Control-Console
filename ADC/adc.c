#include "adc.h"

#include <avr/io.h>

void adc_init(void) {
    ADMUX = (1 << REFS0);

    ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    ADCSRA |= (1 << ADEN);
}

uint16_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));
    return ADC;
}