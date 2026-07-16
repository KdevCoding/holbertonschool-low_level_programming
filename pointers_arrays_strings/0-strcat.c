#include "main.h"

/**
 * _strcat - cobines 2 strings
 * @src: pointer to read string
 * @dest: pointer to destnination for string
 *
 * Return: output dest pointer
 */

char *_strcat(char *dest, char *src)
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
	
	while(i <= sl)
	{
		dest[dl + i] = src[i];
		i++;
	}

	return (dest);
}
