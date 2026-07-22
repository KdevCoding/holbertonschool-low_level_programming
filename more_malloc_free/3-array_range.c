#include <stdlib.h>
#include "main.h"

/**
 * array_range - allocates memory for an array
 * @min: int to start at
 * @max: int to end at
 *
 * Return: null if error or 0 else pointer to array
 */

int *array_range(int min, int max)
{
	int *arr;
	int t;
	int s;
	int i;

	i = 0;
	s = min;
	t = max - min + 1;

	if (min > max)
		return (NULL);

	arr = malloc(sizeof(int) * t);
	if (arr == NULL)
		return (NULL);

	while (i < t)
	{
		arr[i] = s;
		i++;
		s++;
	}
	return (arr);
}
