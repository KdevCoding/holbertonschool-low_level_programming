#include "main.h"
#include <stdio.h>
/**
 * print_to_98 - prints all integers from n to 98
 * @n: value to start from
 *
 */

void print_to_98(int n)
{
	int d = 98 - n;

	if (d > 0)
	{
		while (d-- > 0)
		{
			printf("%d, ", n++);
		}
	}

	else if (d < 0)
	{
		while (d++ < 0)
		{
			printf("%d, ", n--);
		}
	}
	printf("%d\n", n++);
}
