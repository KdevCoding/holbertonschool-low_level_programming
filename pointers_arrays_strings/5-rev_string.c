#include "main.h"

/**
 * rev_string - reverses given var
 * @s: var to reverse
 *
 *
 */

void rev_string(char *s)
{
	int l;
	int i;
	char temp;

	i = 0;
	l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	l--;

	while (l >= i)
	{

		temp = s[i];
		s[i] = s[l];
		s[l] = temp;

		l--;
		i++;
	}
}
