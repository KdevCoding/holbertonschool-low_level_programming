#include "main.h"

/**
 * _isupper - checks if input is uppercase
 * @c: input to check if uppercase
 * Return: 1 if uppercase, 0 otherwise
 */

int _isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}
