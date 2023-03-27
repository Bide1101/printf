#include "main.h"
#include <stdarg.h>

/**
 * print_binary - prints a number in base 2
 * @l: va_list arguments from _printf
 * @f: pointer to the struct
 * Return: the number of char printed
 */

int print_binary(va_list l, flags_t *f)
{
	unsigned int n = va_arg(l, unsigned int);
	char *str = convert(n, 2, 0);

	(void)f;
	return (_puts(str));
}

/**
 * print_octal - prints a number in base 8
 * @l: va_list arguments from _printf
 * @f: pointer to the struct
 * Return: the number of char printed
 */

int print_octal(va_list l, flags_t *f)
{
	unsigned int n = va_arg(l, unsigned int);
	char *str = convert(n, 8, 0);
	int c = 0;

	if (f->hash == 1 && str[0] != '0')
		c += _putchar('0');
	c += _puts(str);
	return (c);
}

/**
 * print_hex - prints a number in hexadecimal base in lowercase
 * @l: va_list arguments from _printf
 * @f: pointer to the struct flags
 * Return: the number of char printed
 */

int print_hex(va_list l, flags_t *f)
{
	unsigned int n = va_arg(l, unsigned int);
	char *str = convert(n, 16, 1);
	int c = 0;

	if (f->hash == 1 && str[0] != '0')
		c += _puts("0x");
	c += _puts(str);
	return (c);
}

/**
 * print_hex_big - prints a number in hexadecimal base in uppercase
 * @l: va_list arguments from _printf
 * @f: pointer to the struct
 * Return: the number of char printed
 */

int print_hex_big(va_list l, flags_t *f)
{
	unsigned int n = va_arg(l, unsigned int);
	char *str = convert(n, 16, 0);
	int c = 0;

	if (f->hash == 1 && str[0] != '0')
		c += _puts("0X");
	c += _puts(str);
	return (c);
}
