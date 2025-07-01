#ifndef USART_H
#define USART_H

#define BAUD 9600
#define F_CPU 16000000UL

#include <avr/io.h>

void usart_init(void);
void usart_destroy(void);
void usart_clear(void);

uint8_t receive_byte(void);
void transmit_byte(uint8_t byte);

void print_format(const char* format, ...);
void print_string(const char* string);
void print_number(int number);
void print_float(float number);

#endif