#include "usart.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define UBRR_VALUE ((F_CPU / (16UL * BAUD) - 1))

void usart_init(void) {
    UBRR0H = (UBRR_VALUE >> 8);
    UBRR0L = UBRR_VALUE;

#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_clear(void) { print_string("\033[2J\033[H"); }

uint8_t receive_byte(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void transmit_byte(uint8_t byte) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = byte;
}

void print_format(const char* format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    print_string(buffer);
}
void print_string(const char* string) {
    while (*string) {
        transmit_byte(*string++);
    }
}
void print_number(int number) {}
void print_float(float number) {}
