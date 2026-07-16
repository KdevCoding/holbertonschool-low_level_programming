#include "main.h"

/**
 * _strcmp - compares s1 to s2
 * @s1: pointer to read string
 * @s2: pointer to compare to s1
 *
 * Return: output the difference in latest comparison
 */

int _strcmp(char *s1, char *s2)
{
	int i;
	int d;

	i = 0;
	d = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{

		d = s1[i] - s2[i];
		if (d < 0 || d > 0)
			break;
		i++;
	}

	return (d);
}
