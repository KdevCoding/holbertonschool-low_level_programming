#include <stdio.h>
#include "main.h"

/**
 * _strcpy - copies string from src to dest (pointers)
 * @src: pointer to read string
 * @dest: pointer to  destnination for string
 *
 * Return: output dest pointer
 */

char *_strcpy(char *dest, char *src)
{
	int l;

	l = 0;
	while (src[l] != '\0')
	{
		dest[l] = src[l];
		l++;
	}
	dest[l] = src[l];

	dest = src;
	return (dest);
}
