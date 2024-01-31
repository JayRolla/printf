#include "main.h"

/**
 * write_string_and_count - Writes a string and counts characters.
 * @str: String to be written
 *
 * Return: Number of characters written
 */
int write_string_and_count(const char *str)
{
    int length = 0;

    /* Calculate the length of the string */
    while (str[length] != '\0')
    {
        length++;
    }

    /* Write the string to the standard output */
    write(1, str, length);

    return (length);
}

/**
 * extract_next_argument - Extracts arguments based on the type specifier.
 * @args: va_list
 * @type: Type of argument ('c' for char, 's' for string)
 *
 * Return: The next argument of the given type
 */
void *extract_next_argument(va_list *args, char type)
{
    /* Check the type specifier and extract the corresponding argument */
    if (type == 'c')
        return ((void *)(long)va_arg(*args, int));
    else if (type == 's')
        return (va_arg(*args, char *));
    else
        return (NULL); /* Add support for additional types as needed */
}

/**
 * _printf - Printf function.
 * @format: Format string
 *
 * Return: Number of characters printed
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
            if (*format == 'c') {
                buffer[0] = (char)(long)extract_next_argument(&args, 'c');
                count += write_string_and_count(buffer);
            } else if (*format == 's') {
                count += write_string_and_count(extract_next_argument(&args, 's'));
            } else if (*format == '%') {
                buffer[0] = '%';
                count += write_string_and_count(buffer);
            }
        }
        else
        {
            /* If not a format specifier, print the character */
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

