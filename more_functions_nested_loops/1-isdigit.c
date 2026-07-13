#include "main.h"

/**
 * _isdigit - checks if input is digit
 * @c: input to check if digit
 * Return: 1 if digit, 0 otherwise
 */

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
