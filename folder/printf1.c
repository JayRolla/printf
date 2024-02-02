#include <stdio.h>
#include "main.h"

/**
 * _printf - A function that produces output according to a format.
 * @format: A character string composed of zero or more directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
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
                                        c = (char)va_arg(arg_list, int);
                                        write(1, &c, 1);
                                        printed_chars++;
                                        break;
                                case 's':
                                {
                                    char *str = va_arg(arg_list, char *);
                                    printed_chars += write(1, str, strlen(str));
                                    break;
                                }
                                case 'd':
                                case 'i':
                                {
                                    int num = va_arg(arg_list, int);
                                    char str_num[12]; /* Buffer big enough for an int. */
                                    sprintf(str_num, "%d", num); /* Convert the int to a string. */
                                    printed_chars += write(1, str_num, strlen(str_num));
                                    break;
                                }
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

int main(void)
{
    _printf("Education is when you read the fine print. Experience is what you get if you don't\n");
    _printf("The number is: %d\n", 42);
    return (0);
}

