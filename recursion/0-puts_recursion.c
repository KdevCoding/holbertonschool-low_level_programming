#include "main.h"

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
		s++;
	if (s[i] != '\0')
	{
		_puts_recursion(s);
	}
	else
		_putchar('\n');
}
