#include "main.h"

/**
 * print_line - '-' n times
 * @n: amount of '-' to print
 */

void print_line(int n)
{
	int i;

	i = 1;
	while (i <= n)
	{
		_putchar('_');
		i++;
	}
	_putchar('\n');

}
