#include "main.h"

/**
 * handle_print - This funnction prints an argument based on its type
 * @fmt: The formatted string to print the arguments
 * @list: the list of arguments to be printed
 * @ind: position
 * @buffer: the buffer array to handle print
 * @flags: to calculate active flags
 * @width: to get the width
 * @precision: This specifies precision
 * @size: This specifies size
 * Return: 1 or 2;
 */

int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknown_len = 0, printed_chars = -1;
	fmt_t format_types[] = {
		{'%', print_percent}, {'b', print_binary}, {'c', print_char},
		{'d', print_int}, {'i', print_int}, {'o', print_octal},
		{'p', print_pointer}, {'r', print_reverse}, {'R', print_rot13string},
		{'s', print_string}, {'S', print_non_printable}, {'u', print_unsigned},
		{'x', print_hexadecimal}, {'X', print_hexa_upper}, {'\0', NULL}
	};
	for (i = 0; format_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == format_types[i].fmt)
			return (format_types[i].fn(list, buffer, flags, width, precision, size));

	if (format_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknown_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknown_len += write(1, &fmt[*ind], 1);
		return (unknown_len);
	}
	return (printed_chars);
}
