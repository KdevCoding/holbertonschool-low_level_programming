#include "main.h"

/**
 * _pow_recursion - x^y
 * @x: x
 * @y: y
 * Return: returns string length
 */

int _pow_recursion(int x, int y)
{
	int res;

	res = x;
	if (y < 0)
		return (-1);

	if (y != 0)
	{
		res *= _pow_recursion(x, y - 1);
	}
	else
		return (1);

	return (res);
}
