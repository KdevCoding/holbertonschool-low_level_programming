#include "main.h"
/**
 * find_prime - checks if prime via testing till root of n
 * @n: number to check
 * @i: iterator
 * Return: 1 if yes 0 if no
 */
int find_prime(int n, int i)
{
	if (i * i > n)
		return (1);
	if (n % i == 0)
		return (0);
	return (find_prime(n, i + 1));
}
/**
 * is_prime_number - checks if number is prime
 * @n: number to check
 *
 * Return: 1 if yes 0 if no
 */

int is_prime_number(int n)
{
	if (n < 2)
		return (0);
	if (n == 2)
		return (0);
	if (n % 2 == 0)
		return (0);

	return (find_prime(n, 3));
}
