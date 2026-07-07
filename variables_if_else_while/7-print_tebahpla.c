#include <stdio.h>

/**
 * main - prints alphabet in lower case
 *
 * Return: 0 always
 */
int main(void)
{
	int i = 122;

	while (i >= 97)
	{
		putchar (i);
		i--;
	}

	putchar ('\n');
	return (0);
}
