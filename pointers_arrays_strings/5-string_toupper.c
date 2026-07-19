/**
 * string_toupper - changes lowercase to uppercase
 * @s: var to change
 *
 * Return: returns changed string
 */

char *string_toupper(char *s)
{
	int l;

	l = 0;
	while (s[l] != '\0')
	{
		if (122 > s[l] && s[l] > 97)
			s[l] -= 32;
		l++;
	}
	return (s);
}
