#include <stdio.h>

/**
 * main - prints alphabet in lower case
 *
 * Return: 0 always
 */
int main(void)
{
	int i = 97;

	while (i <= 122)
	{
		putchar (i);
		i++;
	}

	putchar (' ');
	return (0);
}
