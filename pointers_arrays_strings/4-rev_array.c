#include "main.h"

/**
 * reverse_array - reverses given var
 * @n: var to reverse
 *
 *
 */

void reverse_array(int *a, int n)
{
	int i;
	char temp;

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
