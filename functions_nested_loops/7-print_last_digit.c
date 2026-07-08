#include "main.h"

/**
 * print_last_digit - prints last digit of input
 * @n: input to check
 * Return: value of the last digit
 */

int print_last_digit(int n)
{
	int nl;

	nl = n % 10;
	nl = (nl < 0) ? -nl : nl;
	_putchar('0' + nl);
	return (nl);
}
