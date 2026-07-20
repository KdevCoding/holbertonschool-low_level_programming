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

	if (s == NULL)
		return (0);
	l = 0;
	while (s[l] != '\0')
	{

		l++;
	}
	return (l);
}

/**
 * str_concat - combine given strings
 * @s1: string to write first to mem
 * @s2: second string to write after 1st
 *
 * Return: null if error or 0 else pointer to string
 */

char *str_concat(char *s1, char *s2)
{
	int i;
	int size1;
	int size2;
	int sizeT;
	char *strc;

	i = 0;
	sizeT = 0;

	size1 = _strlen(s1);
	size2 = _strlen(s2);
	sizeT = size1 + size2;

	/**
	 *  if (size == 0)
	 *	return (NULL);
	 */
	strc = malloc(sizeof(char) * (sizeT + 1));
	if (strc == NULL)
		return (NULL);

	while (i < size1)
	{
		strc[i] = s1[i];
		i++;
	}
	while (i < sizeT)
	{
		strc[i] = s2[(i - size1)];
		i++;
	}
	strc[sizeT] = '\0';

	return (strc);
}
