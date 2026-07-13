#include <stdio.h>
#include "main.h"

/**
 * main - Fizz-Buzz test
 *
 * Return: always 0
 */

int  main(void)
{
	int i;
	int f;
	int t;

	i = 1;
	f = 0;
	t = 0;
	while (i <= 100)
	{
		t = i % 3;
		f = i % 5;
		if (t == 0)
			printf("Fizz");

		if (f == 0)
			printf("Buzz");
		if (t != 0 && f != 0)
			printf("%i", i);
		i++;

		putchar(' ');
	}
	putchar('\n');
	return (0);
}
