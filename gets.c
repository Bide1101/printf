#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: Index of the current character in the format string
 * @list: list of arguments.
 * Return: Precision.
 */

int get_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i;
	int precision = -1;

	while (format[curr_i] != '\0')
	{
		if (format[curr_i] == '.')
		{
			precision = 0;
			break;
		}
		curr_i++;
	}

	if (precision == -1)
	{
		return (precision);
	}

	curr_i++;

	if (format[curr_i] == '*')
	{
		precision = va_arg(list, int);
		curr_i++;
	}
	else
	{
		while (is_digit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
			curr_i++;
		}
	}

	*i = curr_i;
	return (precision);
}

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);
}
