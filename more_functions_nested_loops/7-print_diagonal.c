#include "main.h"

/**
 * print_diagonal - '-' n times
 * @n: amount of '-' to print
 */

void print_diagonal(int n)
{
	int i;
	int g;

	g = 1;
	i = 1;
	while (i <= n)
	{
		while (g < i)
		{
			_putchar(' ');
			g++;
		}
		_putchar('\\');
		_putchar('\n');
		g = 1;
		i++;
	}
	if (n <= 0)
		_putchar('\n');
}
