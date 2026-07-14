#include "main.h"

/**
 * print_rev - prints given string in reverse followed by a new line
 * @s: var to print
 *
 *
 */

void print_rev(char *s)
{
	int l;

	l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	l--;

	while (l >= 0)
	{
		_putchar(s[l]);
		l--;
	}
	_putchar('\n');
}
