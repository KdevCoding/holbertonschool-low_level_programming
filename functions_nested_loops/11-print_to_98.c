#include "main.h"

/**
 * jack_bauer - prints every minute of the day
 *
 * Return: always 0
 */

void jack_bauer(void)
{
	int hour = 0, min = 0;

	while (hour < 24)
	{
		while (min < 60)
		{
			_putchar((hour / 10) + '0');
			_putchar((hour % 10) + '0');
			_putchar(':');
			_putchar((min / 10) + '0');
			_putchar((min % 10) + '0');
			_putchar('\n');
			min++;
		}
		hour++;
		min = 0;
	}

}
