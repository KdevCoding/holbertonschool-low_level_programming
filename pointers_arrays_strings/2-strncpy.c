#include "main.h"

/**
 * _strncpy - copies  n bytes of src to dest
 * @src: pointer to read string
 * @dest: pointer to destnination for string
 * @n: amount of bytes
 *
 * Return: output dest pointer
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	i = 0;

	while (src[i] != '\0' && i < n)
	{

		dest[i] = src[i];
		i++;
	}

	while  (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}
