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
    _printf("I'm not going anywhere. You can print that wherever you want to. I'm here and I'm a Spur for life\n");
    return (0);
}

