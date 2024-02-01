#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int _printf(const char *format, ...);
void *extract_next_arg(va_list *parameters, char argType);
int handle_format_specifier(const char **fmt, va_list *parameters);

#endif /* MAIN_H */

