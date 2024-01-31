#include "main.h"

/**
 * write_string_and_count - writes a string and counts characters.
 * @str: string to be written
 *
 * Return: number of characters written
 */
int write_string_and_count(const char *str)
{
    int length = 0;

    /* calculate the length of the string */
    while (str[length] != '\0')
    {
        /* write the character to the standard output */
        putchar(str[length]);
        length++;
    }

    return length;
}

/**
 * extract_next_argument - extracts arguments based on the type specifier.
 * @args: va_list
 * @type: type of argument ('c' for char, 's' for string)
 *
 * Return: the next argument of the given type
 */
void *extract_next_argument(va_list *args, char type)
{
    /* check the type specifier and extract the corresponding argument */
    if (type == 'c')
        return (void *)(long)va_arg(*args, int);
    else if (type == 's')
        return va_arg(*args, char *);
    else
        return NULL;
}

/**
 * _printf - printf function.
 * @format: format string
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char buffer[2] = {0, '\0'};

    /* check if the format string is not NULL */
    if (format == NULL)
        return -1;

    /* start the variable argument list */
    va_start(args, format);

    /* iterate through the format string */
    while (*format != '\0')
    {
        /* check for the '%' character indicating a format specifier */
        if (*format == '%')
        {
            format++;
            /* check the type specifier and print the corresponding argument */
            if (*format == 'c' || *format == 'd' || *format == 'i') {
                char str[12]; /* buffer big enough for INT_MIN */
                sprintf(str, "%d", (int)(long)extract_next_argument(&args, *format));
                count += write_string_and_count(str);
            } 
            /* if the format is 's', we print a string */
            else if (*format == 's') {
                count += write_string_and_count(extract_next_argument(&args, 's'));
            } 
            /* if the format is '%', we print a '%' */
            else if (*format == '%') {
                buffer[0] = '%';
                count += write_string_and_count(buffer);
            }
        }
        else
        {
            /* if it's not a format specifier, we just print the character */
            buffer[0] = *format;
            count += write_string_and_count(buffer);
        }
        format++;
    }

    /* end the variable argument list */
    va_end(args);

    /* return the total number of characters printed */
    return count;
}

