#include "main.h"

/**
 * find_root - finds root via testing
 * @n: number to find root of
 * @i: iterator
 * Return: returns root of n
 */

int find_root(int n, int i)
{
	if (i * i == n)
		return (i);
	if (i * i > n)
		return (-1);
	return (find_root(n, i + 1));
}

/**
 * _sqrt_recursion - finds natural square root of a number
 * @n: number to find square root
 *
 * Return: returns the natural square root of a number or -1 if none
 */

int _sqrt_recursion(int n)
{
	if (n <= 0)
		return (-1);

	return (find_root(n, 0));
}
