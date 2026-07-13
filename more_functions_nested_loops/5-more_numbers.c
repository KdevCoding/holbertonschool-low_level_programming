#include "main.h"

/**
 * more_numbers - prints 0-14 10x
 *
 */

void more_numbers(void)
{
	int i;
	int l;

	i = 0;
	l = 0;

	while (l <= 9)
	{
		while (i <= 14)
		{
			if (i >= 10)
				_putchar('0' + (i / 10));
			_putchar('0' + (i % 10));
			i++;
		}
		i = 0;
		l++;
		_putchar('\n');
	}
}
