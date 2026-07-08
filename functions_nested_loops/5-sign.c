#include "main.h"

/**
 * print_sign - checks if input is postive or 0
 * @n: input to check
 * Return: 1 if positive, 0 if 0, else -
 */

int print_sign(int n)
{
	if (n > 0)
	{
		_putchar('+');
		return (1);
	}
	else if (n == 0)
	{
		_putchar('0');
		return (0);
	}
	else
	{
		_putchar('-');
		return (-1);
	}
}
