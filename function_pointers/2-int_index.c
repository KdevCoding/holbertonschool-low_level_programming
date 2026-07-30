#include <stddef.h>
#include "function_pointers.h"

/**
 * int_index - searches for an integer
 * @array: elements to search
 * @size: size of array
 * @cmp: function to use
 *
 * Return: returns index of matching number, else -1
 */

int int_index(int *array, int size, int (*cmp)(int))
{
	int i;
	int res;

	i = 0;

	if (size <= 0 || array == NULL || cmp == NULL)
		return (-1);

	while (i < size)
	{
		res = cmp(array[i]);
		if (res != 0)
			return (i);

		i++;
	}
	return (-1);
}
