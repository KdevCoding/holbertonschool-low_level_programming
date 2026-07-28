#include <stddef.h>
#include "function_pointers.h"

/**
 * array_iterator - executes given function on each element of given array
 * @array: elements to run fucntion on
 * @size: size of array
 * @action: function to use
 */

void array_iterator(int *array, size_t size, void (*action)(int))
{
	size_t i;

	i = 0;

	while (i < size)
	{
		action(array[i]);
			i++;
	}
}
