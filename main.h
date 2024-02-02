#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void print_char(va_list arg_list, int *printed_chars);
void print_string(va_list arg_list, int *printed_chars);
void print_int(va_list arg_list, int *printed_chars);
int _printf(const char *format, ...);
int _printf1(const char *format, ...);
int _putchar(char c);

#endif /* MAIN_H */

