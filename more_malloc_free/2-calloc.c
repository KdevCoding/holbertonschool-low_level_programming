#include <stdlib.h>
#include "main.h"

/**
 * _calloc - allocates memory for an array
 * @nmemb: amount of elements
 * @size: amount to allocate
 *
 * Return: null if error or 0 else pointer to array
 */

void *_calloc(unsigned int nmemb, unsigned int size)
{
	unsigned char *arr;
	unsigned int i;

	i = 0;

	if (nmemb == 0 || size == 0)
		return (NULL);

	arr = malloc(nmemb * size);
	if (arr == NULL)
		return (NULL);

	while (i < nmemb * size)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}
