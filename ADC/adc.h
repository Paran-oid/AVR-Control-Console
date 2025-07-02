#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

#define POT PC0

#define VOLTMETER PC5

/* Note: This voltmeter is only as accurate as your reference voltage.
 * If you want four digits of accuracy, need to measure your AVCC well.
 * Measure either AVCC of the voltage on AREF and enter it here.
 */
#define REF_VCC 5.053
/* measured division by voltage divider */
#define VOLTAGE_DIV_FACTOR 3.114

void adc_init(uint8_t channel);
void adc_destroy(void);

void adc_sleep_mode_init(void);
void adc_sleep_mode_destroy(void);

uint16_t adc_read(uint8_t channel);

int8_t analog_voltage_read(volatile uint8_t* button_pressed);

#endif