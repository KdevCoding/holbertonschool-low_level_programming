#include <stdarg.h>
#include <stdio.h>
#include "variadic_functions.h"

/**
 * print_numbers - prints given numbers
 * @n: count of vars
 * @separator: separator to use
 *
 */


void print_numbers(const char *separator, const unsigned int n, ...)
{

	va_list ap;
	unsigned int i;

	va_start(ap, n);
	i = 0;

	while (i < n)
	{
		printf("%d", va_arg(ap, int));
		if (separator != NULL && i != n - 1)
			printf("%s", separator);

		i++;
	}
	va_end(ap);
	printf("\n");

}
