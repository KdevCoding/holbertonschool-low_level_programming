#include <stdlib.h>
#include "main.h"

/**
 * _strlen - counts length of string
 * @s: var to count length
 *
 * Return: returns string length
 */

int _strlen(char *s)
{
	int l;

	l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	return (l);
}

/**
 * _strdup - creates an array of given string
 * @str: str to write to mem
 *
 * Return: null if error or 0 else pointer to string
 */

char *_strdup(char *str)
{
	int i;
	int size;
	char *strc;

	size = _strlen(str);
	i = 0;
	/**
	*  if (size == 0)
	*	return (NULL);
	*/
	strc = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);

	while (i <= size)
	{
		strc[i] = str[i];
		i++;
	}

	return (strc);
}
