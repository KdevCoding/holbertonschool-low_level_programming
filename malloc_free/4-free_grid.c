#include <stdlib.h>
#include "main.h"

/**
 * free_grid - frees a 2d array
 * @height: height
 * @grid: pointer to array
 *
 */

void free_grid(int **grid, int height)
{
	while (height > 0)
	{
		height--;
		free(grid[height]);
	}
	free(grid);
}
