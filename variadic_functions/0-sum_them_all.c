#include <stdarg.h>
#include "variadic_functions.h"

/**
 * sum_them_all - sums given numbers
 * @n: 1st number 2 sum
 *
 * Return: total sum
 */


int sum_them_all(const unsigned int n, ...)
{

	va_list ap;
	unsigned int tot;
	unsigned int i;

	va_start(ap, n);
	tot = 0;
	i = 0;

	while (i < n)
	{
		tot += va_arg(ap, int);
		i++;
	}
	va_end(ap);
	return (tot);
}
