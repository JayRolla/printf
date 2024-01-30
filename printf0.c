#include "main.h"

/**
 * writes a string and counts characters.
 * @str: string to be written
 * @count: pointer to the count of characters
 * Return: number of characters written
 */
int write_string_and_count(const char *str, int *count)
{
    int length = 0;

    /* calculate the length of the string */
    while (str[length] != '\0')
    {
        length++;
    }

    /* write the string to the standard output */
    *count += write(1, str, length);

    return length;
}

/**
 * extracts arguments based on the type specifier.
 * @args: va_list
 * @type: type of argument ('c' for char, 's' for string)
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
        return NULL; /* add support for additional types as needed */
}

/**
 * printf function.
 * @format: format string
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
            if (*format == 'c') {
                buffer[0] = (char)(long)extract_next_argument(&args, 'c');
                count += write_string_and_count(buffer, &count);
            } else if (*format == 's') {
                count += write_string_and_count(extract_next_argument(&args, 's'), &count);
            } else if (*format == '%') {
                buffer[0] = '%';
                count += write_string_and_count(buffer, &count);
            }
        }
        else
        {
            /* if not a format specifier, print the character */
            buffer[0] = *format;
            count += write_string_and_count(buffer, &count);
        }
        format++;
    }

    /* end the variable argument list */
    va_end(args);

    /* return the total number of characters printed */
    return count;
}

int main(void) {
    int count = 0;

    /* Your program logic goes here */
    _printf("Hello, %s! This is a number: %d\n", "world", 42);

    /* Print the count of characters written */
    _printf("Total characters written: %d\n", count);

    return 0;
}

