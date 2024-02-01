#include "main.h"

/**
 * write_string_and_count - Writes a string and counts characters.
 * @text: String to be written.
 *
 * Return: Number of characters written.
 */
int write_string_and_count(const char *text)
{
	int strLength = 0;

	while (text[strLength] != '\0')
	{
		putchar(text[strLength]);
		strLength++;
	}

	return (strLength);
}

/**
 * extract_next_arg - Extracts arguments based on the type specifier.
 * @parameters: List of arguments.
 * @argType: Type of argument ('c' for char, 's' for string).
 *
 * Return: The next argument of the given type.
 */
void *extract_next_arg(va_list *parameters, char argType)
{
	if (argType == 'c' || argType == 'd' || argType == 'i')
		return ((void *)(long)va_arg(*parameters, int));
	else if (argType == 's')
		return (va_arg(*parameters, char *));
	else
		return (NULL);
}

/**
 * handle_format_specifier - Handles the format specifier.
 * @fmt: Format string.
 * @parameters: List of arguments.
 *
 * Return: Number of characters printed.
 */
int handle_format_specifier(const char **fmt, va_list *parameters)
{
	int numChars = 0;
	char singleCharStr[2] = {0, '\0'};
	char integerStr[12];

	if (**fmt == 'c')
	{
		char arg = (char)(long)extract_next_arg(parameters, **fmt);

		singleCharStr[0] = arg;
		numChars += write_string_and_count(singleCharStr);
	}
	else if (**fmt == 'd' || **fmt == 'i')
	{
		sprintf(integerStr, "%d", (int)(long)extract_next_arg(parameters, **fmt));
		numChars += write_string_and_count(integerStr);
	}
	else if (**fmt == 's')
	{
		numChars += write_string_and_count(extract_next_arg(parameters, 's'));
	}
	else if (**fmt == '%')
	{
		singleCharStr[0] = '%';
		numChars += write_string_and_count(singleCharStr);
	}

	(*fmt)++;

	return (numChars);
}

/**
 * _printf - Printf function.
 * @fmt: Format string.
 *
 * Return: Number of characters printed.
 */
int _printf(const char *fmt, ...)
{
	va_list parameters;
	int totalCount = 0;
	char singleCharStr[2] = {0, '\0'};

	if (fmt == NULL)
		return (-1);

	va_start(parameters, fmt);

	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			totalCount += handle_format_specifier(&fmt, &parameters);
		}
		else
		{
			singleCharStr[0] = *fmt;
			totalCount += write_string_and_count(singleCharStr);
			fmt++;
		}
	}

	va_end(parameters);

	return (totalCount);
}

int main(void)
{
	_printf("Character: %c\n", 'A');
	_printf("String: %s\n", "Hello, world!");
	_printf("Percent sign: %%\n");

	return (0);

}

