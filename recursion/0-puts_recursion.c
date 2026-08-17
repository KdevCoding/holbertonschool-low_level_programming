#include "main.h"

void _puts_recursion(char *s)
{
	unsigned int i;
	
	i = 0;

	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
	_putchar('\n');
}
