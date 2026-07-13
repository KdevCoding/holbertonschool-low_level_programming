#include "main.h"

/**
 * print_triangle - prints a traigle whith dimension of size
 * @size: dimensions of triangle
 */

void print_triangle(int size)
{
	int h;
	int g;
	int t;

	h = 1;
	g = 1;
	t = 1;

	while (h <= size)
	{
		while (g <= (size - h))
		{
			_putchar(' ');
			g++;
		}
		g = 1;
		while (t <= h)
		{
			_putchar('#');
			t++;
		}
		t = 1;

		_putchar('\n');
		h++;
	}
	if (size <= 0)
		_putchar('\n');
}
