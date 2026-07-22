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
 * string_nconcat - combine given strings (n of s2)
 * @s1: string to write first to mem
 * @s2: second string to write after 1st
 * @n: amount of string 2 to copy
 *
 * Return: null if error or 0 else pointer to string
 */

char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	unsigned int i;
	unsigned int size1;
	unsigned int size2;
	unsigned int sizeT;
	char *strc;

	i = 0;
	sizeT = 0;

	size1 = _strlen(s1);
	size2 = _strlen(s2);
	sizeT = size1 + size2;

	if (sizeT > (size1 + n))
		sizeT = size1 + n;

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
