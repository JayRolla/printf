#include "main.h"

/*
 * This function extracts the next argument from the variable argument list
 * based on the type specifier.
 *
 * parameters: This is the list of arguments.
 * argType: This is the type of argument. 'c' is for char, 's' is for string.
 *
 * The function returns the next argument of the given type.
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

/*
 * This function handles the format specifier.
 *
 * fmt: This is the format string.
 * parameters: This is the list of arguments.
 *
 * The function returns the number of characters printed.
 */
int handle_format_specifier(const char **fmt, va_list *parameters)
{
	int numChars = 0;
	char integerStr[12];

	if (**fmt == 'c')
	{
		char arg = (char)(long)extract_next_arg(parameters, **fmt);

		putchar(arg);
		numChars++;
	}
	else if (**fmt == 'd' || **fmt == 'i')
	{
		sprintf(integerStr, "%d", (int)(long)extract_next_arg(parameters, **fmt));
		fputs(integerStr, stdout);
		numChars += strlen(integerStr);
	}
	else if (**fmt == 's')
	{
		fputs(extract_next_arg(parameters, 's'), stdout);
		numChars += strlen(extract_next_arg(parameters, 's'));
	}
	else if (**fmt == '%')
	{
		putchar('%');
		numChars++;
	}

	(*fmt)++;

	return (numChars);
}

/*
 * This is the main _printf function.
 *
 * fmt: This is the format string.
 *
 * The function returns the number of characters printed.
 */
int _printf(const char *fmt, ...)
{
	va_list parameters;
	int totalCount = 0;

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
			putchar(*fmt);
			totalCount++;
			fmt++;
		}
	}

	va_end(parameters);

	return (totalCount);
}

/*
 * This is the main function.
 *
 * The function returns 0 if successful, non-zero otherwise.
 */
int main(void)
{
	_printf("char: %c\n", 'M');
	_printf("Str: %s\n", "Molapo");
	_printf("percent sign: %%\n");

	return (0);
}

