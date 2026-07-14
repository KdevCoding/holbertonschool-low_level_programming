#include "main.h"

/**
 * puts2 - prints every other char of given string followed by a new line
 * @str: var to print
 *
 *
 */

void puts2(char *str)
{
	int l;

	l = 0;
	while (str[l] != '\0')
	{
		if (l % 2 == 0)
			_putchar(str[l]);
		l++;
	}
	_putchar('\n');
}
