#include "main.h"
#include <stdarg.h>
#include <stddef.h>

/**
 * print_bigS - Non printable characters
 * @l: va_list arguments from _printf
 * @f: pointer to the struct flags
 * Return: number of char printed
 */

int print_bigS(va_list l, flags_t *f)
{
	int i, c = 0;
	char *res;
	char *s = va_arg(l, char *);

	(void)f;
	if (!s)
		return (_puts("(null)"));

	for (i = 0; s[i]; i++)
	{
		if (s[i] > 0 && (s[i] < 32 || s[i] >= 127))
		{
			_puts("\\x");
			c += 2;
			res = convert(s[i], 16, 0);
			if (!res[1])
				c += _putchar('0');
			c += _puts(res);
		}
		else
			c += _putchar(s[i]);
	}
	return (c);
}


/**
 * print_percent - prints a percent
 * @l: va_list arguments
 * @f: pointer to the struct flags
 * Return: number of char printed
 */

int print_percent(va_list l, flags_t *f)
{
	(void)l;
	(void)f;
	return (_putchar('%'));
}

/**
 * print_rot13 - prints string with rot13
 * @l: list of arguments
 * @f: pointer to the struct flags
 * Return: length of string
 */

int print_rot13(va_list l, flags_t *f)
{
	int i, j;
	char rot13[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char ROT13[] = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *s = va_arg(l, char *);

	(void)f;
	for (j = 0; s[j]; j++)
	{
		if (s[j] < 'A' || (s[j] > 'Z' && s[j] < 'a') || s[j] > 'z')
			_putchar(s[j]);
		else
		{
			for (i = 0; i <= 52; i++)
			{
				if (s[j] == rot13[i])
					_putchar(ROT13[i]);
			}
		}
	}

	return (j);
}


/**
 * print_rev - prints string in reverse
 * @l: argument from _printf
 * @f: pointer to the struct flags
 * Return: length of the printed string
 */

int print_rev(va_list l, flags_t *f)
{
	int i = 0, j;
	char *str = va_arg(l, char *);

	(void)f;
	if (!str)
		str = "(null)";

	while (str[i])
		i++;

	for (j = i - 1; j >= 0; j--)
		_putchar(str[j]);
	return (i);
}
