#include "main.h"

/**
 * _strlen - counts length of string
 * @s: var to count length
 *
 * Return: returns string length
 */

int _strlen_recursion(char *s)
{
	int l;

	l = 0;
	if (s[l] != '\0')
	{
		s++;
		l++;
		l += _strlen_recursion(s);
	}
	return (l);
}
