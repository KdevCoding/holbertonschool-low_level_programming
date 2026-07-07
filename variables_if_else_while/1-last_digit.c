#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * main - generates a random number and prints it to terminals
 *
 * Return: 0 always
 */
int main(void)
{
	int n;
	int nl;

	srand(time(0));
	n = rand() - RAND_MAX / 2;
	nl = n % 10;

	if (nl > 5)
	{
		printf("Last digit of %i is %i and is greater than 5\n", n, nl);
	}
	else if (n < 0)
	{
		printf("Last digit of %i is %i and is 0\n", n, nl);
	}
	else
	{
		printf("Last digit of %i is %i and  is less than 6 and not 0\n", n, nl);
	}

	return (0);
}
