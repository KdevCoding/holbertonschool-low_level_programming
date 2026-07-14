/**
 * swap_int - swapts the value of 2 ints
 * @a: var to edit
 * @b: var to edit
 *
 */

void swap_int(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}
