#include "main.h"

/**
 * _puts - prints given string folled by a new line
 * @str: var to print
 *
 *
 */

void _puts(char *str)
{
	int l;

	l = 0;
	while (str[l] != '\0')
	{
		_putchar(str[l]);
		l++;
	}
	_putchar('\n');
}
