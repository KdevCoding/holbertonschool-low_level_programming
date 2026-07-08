#include "main.h"

/**
 * _isalpha - checks if input is a letter
 * @c: input to check if letter
 * Return: 1 if letter, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
