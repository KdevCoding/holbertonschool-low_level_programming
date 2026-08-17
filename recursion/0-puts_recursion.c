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
 * _puts_recursion - prints a string
 * @s: string to print
 *
 *
 */

void _puts_recursion(char *s)
{
	unsigned int i;

	i = 0;
	_putchar(s[i]);

	if (_strlen(s) == 0)
		return;

	s++;
	if (s[i] != '\0')
	{
		_puts_recursion(s);
	}
	else
		_putchar('\n');
}
