#include "main.h"

/**
 * puts_half - prints 2nd half given string followed by a new line
 * @str: var to print
 *
 *
 */

void puts_half(char *str)
{
	int l;
	int len;

	l = 0;
	while (str[l] != '\0')
	{
		l++;
	}
	len = l;

	if (len % 2 == 0)
		l = len / 2;
	else
		l = (len + 1) / 2;

	while (str[l] != '\0')
	{
		_putchar(str[l]);
		l++;
	}
	_putchar('\n');
}
