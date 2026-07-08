#include "main.h"

/**
 * print_alphabet_x10 - prints alphabet x10  in lower case using ascii
 *
 * Return: 0 always
 */
int print_alphabet_x10(void)
{
	int l = 0;

	while (l < 10)
	{
		int i = 97;

		while (i <= 122)
		{
			_putchar (i);
			i++;
		}

		_putchar ('\n');
		l++;
	}
	return (0);
}
