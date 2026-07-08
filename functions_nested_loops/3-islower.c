#include "main.h"

/**
 * _islower - checks if input is lower case
 * @c: input to check if lowercase
 * Return: 1 if lowercase, 0 otherwise
 */

int _islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else
		return (0);
}
