#include <stdlib.h>
#include "main.h"

/**
 * alloc_grid - creats a 2d array of int
 * @width: width
 * @height: height
 *
 * Return: null if error or 0 else pointer to array
 */

int **alloc_grid(int width, int height)
{
	int h;
	int w;
	int **arr;

	if (width <= 0 || height <= 0)
		return (NULL);

	arr = malloc(sizeof(int *) * height);
	if (arr == NULL)
		return (NULL);

	h = 0;
	while (h < height)
	{
		arr[h] = malloc(sizeof(int) * width);
		if (arr[h] == NULL)
			return (NULL);

		w = 0;
		while (w < width)
		{
			arr[h][w] = 0;
			w++;
		}
		h++;
	}

	return (arr);
}
