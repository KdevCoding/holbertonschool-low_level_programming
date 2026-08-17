#include "main.h"

/**
 * _strlen - counts length of string
 * @s: var to count length
 *
 * Return: returns string length
 */

int _strlen(char *s)
{
	int l;

	l = 0;
	if (s[l] != '\0')
	{
		s++;
		l++;
		l += _strlen(s);
	}
	return (l);
}

/**
 * _print_rev_recursion - prints a string in reverse
 * @s: string to print
 *
 *
 */

void _print_rev_recursion(char *s)
{
	unsigned int i;

	i = 0;

	if (_strlen(s) == 0)
	{
		return;
	}

	if (s[i] != '\0')
	{
		_print_rev_recursion(s + 1);
	}
	_putchar(s[i]);
}
