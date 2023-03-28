#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: chars.
 */
int _printf(const char *format, ...)
{
	int b, print = 0, printed_char = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (b = 0; format && format[b] != '\0'; b++)
	{
		if (format[b] != '%')
		{
			buffer[buff_ind++] = format[b];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_char++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &b);
			width = get_width(format, &b, list);
			precision = get_precision(format, &b, list);
			size = get_size(format, &b);
			++b;
			print = handle_print(format, &b, list, buffer,
				flags, width, precision, size);
			if (print == -1)
				return (-1);
			printed_char += print;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_char);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length
 * Return: Void
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
