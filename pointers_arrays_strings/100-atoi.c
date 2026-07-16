#include "main.h"

/**
 * _atoi - convert string to int
 * @s: str to convert
 *
 * Return: output conversion
 */

int _atoi(char *s)
{
	int i;
	int n;
	int sign;

	sign = 1;
	n = 0;
	i = 0;

	while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}

	while (s[i] >= '0' && s[i] <= '9')
	{
		n = (n * 10) + (unsigned int)(s[i] - '0');
		i++;
	}

	return (sign * (int)n);
}

