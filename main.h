#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdarg.h>
int print_address(va_list l, flags_t *f);
int _printf(const char *format, ...);
int _putchar(char c);
int _puts(char *str);

#endif
