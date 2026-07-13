#include "main.h"

/**
 * print_square - prints n x n '#'
 * @n: amount of squares/ # to print
 */

void print_square(int n)
{
	int r;
	int c;

	r = 1;
	c = 1;
	while (c <= n)
	{
		while (r <= n)
		{
			_putchar('#');
			r++;
		}
		_putchar('\n');
		r = 1;
		c++;
	}
	if (n <= 0)
		_putchar('\n');
}
