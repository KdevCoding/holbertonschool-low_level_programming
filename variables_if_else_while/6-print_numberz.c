#include <stdio.h>

/**
 * main - prints alphabet in lower case
 *
 * Return: 0 always
 */
int main(void)
{
	int i = 48;

	while (i <= 57)
	{
		putchar(i);
		i++;
	}

	putchar ('\n');
	return (0);
}
