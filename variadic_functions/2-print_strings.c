#include <stdarg.h>
#include <stdio.h>
#include "variadic_functions.h"

/**
 * print_strings - prints given strings
 * @n: count of vars
 * @separator: separator to use
 *
 */


void print_strings(const char *separator, const unsigned int n, ...)
{
	va_list ap;
	unsigned int i;

	va_start(ap, n);
	i = 0;

	while (i < n)
	{
		printf("%s", va_arg(ap, char *));
		if (separator != NULL && i != n - 1)
			printf("%s", separator);

		i++;
	}
	va_end(ap);
	printf("\n");

}
