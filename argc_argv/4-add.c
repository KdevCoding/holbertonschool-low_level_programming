#include <stdio.h>

/**
 * _isdigit - checks if input is digit
 * @c: input to check if digit
 * Return: 1 if digit, 0 otherwise
 */

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/**
 * _atoi - convert string to int
 * @s: str to convert
 *
 * Return: output conversion
 */

int _atoi(char *s)
{
	int i;
	unsigned int n;
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

	if (sign == -1)
		n = -n;

	return ((int)n);
}

/**
 * is_valid_number - checks if input is number
 * @str: input to check if digit
 * Return: 1 if number, 0 otherwise
 */

int is_valid_number(char *str)
{
	int j;

	j = 0;
	if (str[j] == '+' || str[j] == '-')
		j++;
	while (str[j])
	{
		if (!_isdigit(str[j]))
			return (0);
		j++;
	}
	return (1);
}

/**
 * main - adds positive numbers
 * @argc: amount of arguments
 * @argv: arguments
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	int i;
	int n;
	int res;

	i = 1;
	res = 0;
	while (i < argc)
	{
		if (is_valid_number(argv[i]))
		{
			n = _atoi(argv[i]);
			res += n;
		}

		else
		{
			printf("Error\n");
			return (1);
		}

		i++;
	}

	printf("%d\n", res);
	return (0);
}
