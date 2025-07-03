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
void usart_destroy(void) {
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));

    // disable interrupts
    UCSR0B &= ~((1 << RXCIE0) | (1 << TXCIE0) | (1 << UDRIE0));

    UCSR0C = 0;

    UBRR0H = 0;
    UBRR0L = 0;

    UCSR0A = 0;
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
void print_number(int number) {
    char buf[12];  // enough for -32768 to 32767 plus null
    char* p = buf + sizeof(buf) - 1;
    unsigned int n;
    *p = '\0';

    if (number < 0) {
        n = -number;
    } else {
        n = number;
    }

    do {
        *(--p) = '0' + (n % 10);
        n /= 10;
    } while (n > 0);

    if (number < 0) {
        *(--p) = '-';
    }

    print_string(p);
}
void print_float(float number) {
    char buf[32];
    dtostrf(number, 8, 4, buf);
    print_string(buf);

    //     if (number < 0) {
    //         print_string("-");
    //         number = -number;
    //     }

    //     int int_part = (int)number;
    //     int frac_part =
    //         (int)((number - int_part) * 100 + 0.5f);  // round to 2 decimals

    //     print_number(int_part);
    //     print_string(".");

    //     // Print leading zero if needed
    //     if (frac_part < 10) {
    //         print_string("0");
    //     }
    //     print_number(frac_part);
}
