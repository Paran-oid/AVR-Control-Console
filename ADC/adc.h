#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

#define POT PC0

void adc_init(void);
void adc_destroy(void);
uint16_t adc_read(uint8_t channel);

#endif