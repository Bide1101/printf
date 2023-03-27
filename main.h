#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdarg.h>
int print_binary(va_list l, flags_t *f);
int print_hex(va_list l, flags_t *f);
int print_hex_big(va_list l, flags_t *f);
int print_octal(va_list l, flags_t *f);
int print_address(va_list l, flags_t *f);
int _printf(const char *format, ...);
int _putchar(char c);
int _puts(char *str);
char *convert(unsigned long int num, int base, int lowercase);

#endif
