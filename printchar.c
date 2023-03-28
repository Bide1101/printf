#include "main.h"

/**
 * handle_write_char - This function prints a string
 * @c: the char type
 * @buffer: this is the buffer array to handle print
 * @flags:  this calculates active flags
 * @width: this gets the width
 * @precision: this specifies the precision
 * @size: this specifies the size
 * Return: count of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and padded at buffer's right */
	int b = 0;
	char pad = ' ';

	(void)precision;
	(void)size;

	if (flags & F_ZERO)
		pad = '0';

	buffer[b++] = c;
	buffer[b] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (b = 0; b < width - 1; b++)
			buffer[BUFF_SIZE - b - 2] = pad;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - b - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - b - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - This prints a string
 * @is_negative: a list of arguments
 * @ind: types of char
 * @buffer: this is the buffer array to handle print
 * @flags: This calculates active flags
 * @width: This specifies the width
 * @precision: This specifies the precision
 * @size: This specifies the size
 * Return: count of chars printed
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - ind - 1;
	char pad = ' ', extra_c = 0;

	(void)size;

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		extra_c = '-';
	else if (flags & F_PLUS)
		extra_c = '+';
	else if (flags & F_SPACE)
		extra_c = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		len, pad, extra_c));
}

/**
 * write_num - This writes a number using a bufffer
 * @ind: index position at which the number starts on the buffer
 * @buffer: the buffer to be used
 * @flags: calculates active flags
 * @width: this gets the width
 * @prec: this specifies the precision
 * @length: the shows the length of the number
 * @padd: a char used to pad
 * @extra_c: an extra char
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int b, pad_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (b = 1; b < width - length + 1; b++)
			buffer[b] = padd;
		buffer[b] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], b - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/*an extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], b - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			return (write(1, &buffer[pad_start], b - pad_start) +
				write(1, &buffer[ind], length - (1 - pad_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - this function writes an unsigned number
 * @is_negative: This indicates if num is negative
 * @ind: position at which the number starts in the buffer
 * @buffer: an array of chars
 * @flags: This specifies active flags
 * @width: this specifies width
 * @precision: this specifies precision
 * @size: this specifies sizes
 * Return: the number of written chars
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the buffer's right and starts at position i */
	int len = BUFF_SIZE - ind - 1, b = 0;
	char pad = ' ';

	(void)is_negative;
	(void)size;

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < len)
		pad = ' ';

	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > len)
	{
		for (b = 0; b < width - len; b++)
			buffer[b] = pad;

		buffer[b] = '\0';
		/*Assign an extra char to the left of the buffer[buffer>padd]*/
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], b));
		}
		else /* Assign an extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], b) + write(1, &buffer[ind], len));
		}
	}

	return (write(1, &buffer[ind], len));
}

/**
 * write_pointer - This function writes a memory address
 * @buffer: Arrays of chars
 * @ind: the position at which the number starts in the buffer
 * @length: the length of number
 * @width: this specifies the width
 * @flags: specifies active flags
 * @padd: the char representing the padding used
 * @extra_c: this char represents an extra char
 * @padd_start: position which padding would start
 * Return: Number of written chars
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int b;

	if (width > length)
	{
		for (b = 3; b < width - length + 3; b++)
			buffer[b] = padd;
		buffer[b] = '\0';
		/* Assign an extra char to the left of the buffer */
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], b - 3));
		}
		/* Pad an extra char to the left of the buffer */
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], b - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], b - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
