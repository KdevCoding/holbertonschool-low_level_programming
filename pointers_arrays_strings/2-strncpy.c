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
	int sl;
	int i;

	i = 0;
	sl = 0;

	while (src[sl] != '\0')
	{
		sl++;
	}

	while (i < n)
	{
		if (src[i] == NULL)
			dest[i] = "";
		dest[i] = src[i];
		i++;
	}

	return (dest);
}
