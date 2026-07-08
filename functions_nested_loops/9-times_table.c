#include "main.h"

/**
 * times_table - prints 9 times table
 *
 * Return: always 0
 */

void times_table(void)
{
	int n = 0, i = 0, l = 0;

	while (n <= 81)
	{
		l = 0;
		n = 0;

		while (l < 10)
		{
			if (n < 10)
			{
				_putchar(' ');
				_putchar('0' + n);
			}
			else
			{
				_putchar((n / 10) + '0');
				_putchar((n % 10) + '0');
			}
			if (l < 9)
			{
				_putchar(44);
				_putchar(' ');
			}
			n += i;
			l++;
		}
		i++;
		_putchar('\n');
	}
}
