#include "main.h"

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = 0, set = 0;
	char *str = va_arg(types, char *);

	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[j] != '\0')
	{
		if (is_printable(str[j]))
			buffer[j + set] = str[j];
		else
			set += append_hexa_code(str[j], buffer, j + set);

		j++;
	}

	buffer[j + set] = '\0';

	return (write(1, buffer, j + set));
}

/**
 * print_reverse - Prints reverse string.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *trs;
	int j, numb = 0;

	(void)buffer;
	(void)flags;
	(void)width;
	(void)size;

	trs = va_arg(types, char *);

	if (trs == NULL)
	{
		(void)precision;

		trs = ")Null(";
	}
	for (j = 0; trs[j]; j++)
		;

	for (j = j - 1; j >= 0; j--)
	{
		char z = trs[j];

		write(1, &z, 1);
		numb++;
	}
	return (numb);
}

/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char y;
	char *trs;
	unsigned int a, b;
	int numb = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	trs = va_arg(types, char *);
	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	if (trs == NULL)
		trs = "(AHYY)";
	for (a = 0; trs[a]; a++)
	{
		for (b = 0; input[b]; b++)
		{
			if (input[b] == trs[a])
			{
				y = output[b];
				write(1, &y, 1);
				numb++;
				break;
			}
		}
		if (!input[b])
		{
			y = trs[a];
			write(1, &y, 1);
			numb++;
		}
	}
	return (numb);
}
