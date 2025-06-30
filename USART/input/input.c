#include "input.h"

#include "adc.h"
#include "usart.h"

uint8_t handle_option(void) {
    uint16_t potention_meter_val = adc_read(POT_OPTION);
    potention_meter_val >>= 7;  // equivalent to p = p >> 7;
    if (potention_meter_val >= 3) {
        potention_meter_val -= 3;
    }

    return potention_meter_val;
}