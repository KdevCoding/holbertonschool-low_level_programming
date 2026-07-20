/**
 * leet - encodes a string into leet
 * @s: var to change
 *
 * Return: returns pointer to changed string
 */

char *leet(char *s)
{
	char letters[] = "aAeEoOtTlL";
	char nums[] = "4433007711";
	int i;
	int j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (letters[j] != '\0')
		{
			if (s[i] == letters[j])
				s[i] = nums[j];
			j++;
		}
		i++;
	}
	return (s);
}
