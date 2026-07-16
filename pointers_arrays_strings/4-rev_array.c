#include "main.h"

/**
 * reverse_array - reverses given var
 * @a: var to reverse
 * @n: length of array
 *
 */

void reverse_array(int *a, int n)
{
	int i;
	int temp;

	i = 0;
	n--;
	while (n >= i)
	{

		temp = a[i];
		a[i] = a[n];
		a[n] = temp;

		n--;
		i++;
	}
}
