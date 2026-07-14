#include <stdio.h>
#include "main.h"

/**
 * print_array - prints n elements of given array followed by a new line
 * @a: array to print
 * @n: amount of elements to print
 *
 */

void print_array(int *a, int n)
{
	int l;

	l = 0;
	while (l < n)
	{
		if (l != (n - 1))
			printf("%d, ", a[l]);
		else
			printf("%d", a[l]);
		l++;
	}
	printf("\n");
}
