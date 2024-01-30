#include "main.h"



/* function to write a string and count the characters written */
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

/* function to extract the next argument based on the type specifier */
void *extract_next_argument(va_list *args, char type)
{
    /* check the type specifier and extract the corresponding argument */
    if (type == 'c')
        return (void *)(long)va_arg(*args, int);
    else if (type == 's')
        return va_arg(*args, char *);
    else if (type == 'd' || type == 'i')
        return (void *)(long)va_arg(*args, int);
    else
        return NULL; /* add support for additional types as needed */
}

/* printf function for task 2 */
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
            } else if (*format == 'd' || *format == 'i') {
                int num = (int)(long)extract_next_argument(&args, 'd');
                char num_str[12];  /* assuming 32-bit int */
                sprintf(num_str, "%d", num);
                count += write_string_and_count(num_str, &count);
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

