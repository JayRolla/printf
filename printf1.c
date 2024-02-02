#include "main.h"

void print_char(va_list arg_list, int *printed_chars)
{
	char c = (char)va_arg(arg_list, int);

	write(1, &c, 1);
	(*printed_chars)++;
}

void print_string(va_list arg_list, int *printed_chars)
{
	char *str = va_arg(arg_list, char *);

	*printed_chars += write(1, str, strlen(str));
}

void print_int(va_list arg_list, int *printed_chars)
{
	int num = va_arg(arg_list, int);
	char str_num[12]; /* Buffer big enough for an int. */

	sprintf(str_num, "%d", num);
	*printed_chars += write(1, str_num, strlen(str_num));
}

/**
 * _printf1 - A function that produces output according to a format.
 * @format: A character string composed of zero or more directives.
 *
 * Return: The number of characters printed.
 */
int _printf1(const char *format, ...)
{
	va_list arg_list;
	int index, printed_chars = 0;
	char c;

	va_start(arg_list, format);

	for (index = 0; format[index] != '\0'; index++)
	{
		if (format[index] != '%')
		{
			c = format[index];
			write(1, &c, 1);
			printed_chars++;
		}
		else
		{
			index++;
			switch (format[index])
			{
			case 'c':
				print_char(arg_list, &printed_chars);
				break;
			case 's':
				print_string(arg_list, &printed_chars);
				break;
			case 'd':
			case 'i':
				print_int(arg_list, &printed_chars);
				break;
			case '%':
				c = '%';
				write(1, &c, 1);
				printed_chars++;
				break;
			}
		}
	}

	va_end(arg_list);

	return (printed_chars);
}

