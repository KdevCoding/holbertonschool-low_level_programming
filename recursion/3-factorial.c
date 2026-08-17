#include "main.h"

/**
 * factorial - get factorial of given number
 * @n: number to get fac of
 *
 * Return: returns string length
 */

int factorial(int n)
{
	if (n < 0)
		return (-1);

	if (n != 0)
	{
		n *= factorial(n - 1);
	}
	else
		n = 1;

	return (n);
}
