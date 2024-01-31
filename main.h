#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/* prototypes */
int _printf(const char *format, ...);
int write_string_and_count(const char *str);
void *extract_next_argument(va_list *args, char type);

#endif /* MAIN_H */

