#include <stdlib.h>
#include "main.h"

/**
 * malloc_checked - allocate mem using malloc
 * @b: amount to allocate
 *
 *
 * Return: null if error or 0 else pointer to string
 */

void *malloc_checked(unsigned int b)
{
	void *ptr;

	ptr = malloc(b);
	if (ptr == NULL)
	{
		free(ptr);
		exit (98);
	}

	return (ptr);
}
