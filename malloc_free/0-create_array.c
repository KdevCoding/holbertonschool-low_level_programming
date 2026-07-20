#include <stdlib.h>
#include "main.h"

/**
 * create_array - creates an array of chars
 * @size: size of array
 * @c: char to initializes with
 *
 * Return: null if error or 0 else pointer to string
 */

char *create_array(unsigned int size, char c)
{
	char *str;
	unsigned int i;

	i = 0;
	if (size == 0)
		return (NULL);

	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);

	while (i <= size)
	{
		str[i] = c;
		i++;
	}

	return (str);
}
