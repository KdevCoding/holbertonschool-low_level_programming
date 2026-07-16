#include "main.h"

/**
 * _strncat - combines n bytes of src to dest
 * @src: pointer to read string
 * @dest: pointer to destnination for string
 * @n: amount of bytes
 *
 * Return: output dest pointer
 */

char *_strncat(char *dest, char *src, int n)
{
	int dl;
	int sl;
	int i;

	i = 0;
	dl = 0;
	sl = 0;
	while (dest[dl] != '\0')
	{
		dl++;
	}

	while (src[sl] != '\0')
	{
		sl++;
	}

	while (i <= sl && i < n)
	{
		dest[dl + i] = src[i];
		i++;
	}

	return (dest);
}
