#include "main.h"

/**
 * is_separator - checks if a character is a word separator
 * @c: character to check
 *
 * Return: 1 if separator, 0 otherwise
 */
int is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ';' ||
	    c == '.' || c == '!' || c == '?' || c == '"' || c == '(' ||
	    c == ')' || c == '{' || c == '}')
		return (1);
	return (0);
}

/**
 * cap_string - capitalizes the first letter of every word in a string
 * @s: string to modify
 *
 * Return: pointer to the modified string
 */
char *cap_string(char *s)
{
	int i;
	int prev_is_sep;

	i = 0;
	prev_is_sep = 1;

	while (s[i] != '\0')
	{
		if (prev_is_sep && s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;

		prev_is_sep = is_separator(s[i]);
		i++;
	}

	return (s);
}
