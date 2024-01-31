#include "main.h"

/**
 * write_string_and_count - Writes a string and counts characters.
 * @str: String to be written.
 *
 * Return: Number of characters written.
 */
int write_string_and_count(const char *str)
{
	int length = 0;

	/* Calculate the length of the string */
	while (str[length] != '\0')
	{
		/* Write the character to the standard output */
		putchar(str[length]);
		length++;
	}

	return (length);
}

/**
 * extract_next_argument - Extracts arguments based on the type specifier.
 * @args: List of arguments.
 * @type: Type of argument ('c' for char, 's' for string).
 *
 * Return: The next argument of the given type.
 */
void *extract_next_argument(va_list *args, char type)
{
	/* Check the type specifier and extract the corresponding argument */
	if (type == 'c' || type == 'd' || type == 'i')
		return (void *)(long)va_arg(*args, int);
	else if (type == 's')
		return va_arg(*args, char *);
	else
		return NULL;
}

/**
 * _printf - Printf function.
 * @format: Format string.
 *
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char buffer[2] = {0, '\0'};

	/* Check if the format string is not NULL */
	if (format == NULL)
		return (-1);

	/* Start the variable argument list */
	va_start(args, format);

	/* Iterate through the format string */
	while (*format != '\0')
	{
		/* Check for the '%' character indicating a format specifier */
		if (*format == '%')
		{
			format++;
			/* Check the type specifier and print the corresponding argument */
			if (*format == 'c' || *format == 'd' || *format == 'i')
			{
				char str[12]; /* Buffer big enough for INT_MIN */
				sprintf(str, "%d", (int)(long)extract_next_argument(&args, *format));
				count += write_string_and_count(str);
			}
			/* If the format is 's', we print a string */
			else if (*format == 's')
			{
				count += write_string_and_count(extract_next_argument(&args, 's'));
			}
			/* If the format is '%', we print a '%' */
			else if (*format == '%')
			{
				buffer[0] = '%';
				count += write_string_and_count(buffer);
			}
		}
		else
		{
			/* If it's not a format specifier, just print the character */
			buffer[0] = *format;
			count += write_string_and_count(buffer);
		}
		format++;
	}

	/* End the variable argument list */
	va_end(args);

	/* Return the total number of characters printed */
	return (count);
}

