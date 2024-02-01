#include "main.h"

/**
 * write_string_and_count - Writes a string and counts characters.
 * @str: String to be written.
 * @count: Pointer to the count of characters.
 *
 * Return: Length of the string.
 */
int write_string_and_count(const char *str, int *count)
{
	int length = 0;

	while (str[length] != '\0')
	{
		length++;
	}

	*count += write(1, str, length);

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
	if (type == 'c' || type == 'd' || type == 'i')
		return ((void *)(long)va_arg(*args, int));
	else if (type == 's')
		return (va_arg(*args, char *));
	else
		return (NULL);
}

/**
 * handle_format_specifier - Handles the format specifier.
 * @format: Format string.
 * @args: List of arguments.
 * @count: Pointer to the count of characters.
 *
 * Return: Number of characters printed.
 */
int handle_format_specifier(const char **format, va_list *args, int *count)
{
	char buffer[2] = {0, '\0'};
	char num_str[12];

	if (*format == 'c')
	{
		buffer[0] = (char)(long)extract_next_argument(args, 'c');
		*count += write_string_and_count(buffer, count);
	}
	else if (*format == 's')
	{
		*count += write_string_and_count(extract_next_argument(args, 's'), count);
	}
	else if (*format == 'd' || *format == 'i')
	{
		int num = (int)(long)extract_next_argument(args, 'd');

		sprintf(num_str, "%d", num);
		*count += write_string_and_count(num_str, count);

	}

	return (*count);
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

	if (format == NULL)
		return (-1);

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			count += handle_format_specifier(&format, &args, &count);
		}
		else
		{
			buffer[0] = *format;
			count += write_string_and_count(buffer, &count);
		}
		format++;
	}

	va_end(args);

	return (count);
}

