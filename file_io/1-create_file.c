#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "main.h"

/**
 * _strlen - counts length of string
 * @s: var to count length
 *
 * Return: returns string length
 */

int _strlen(char *s)
{
	int l;

	l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	return (l);
}

/**
 * create_file - creates a file
 * @filename: file to create
 * @text_content: text to write
 *
 * Return: 1 on success else -1
 */
int create_file(const char *filename, char *text_content)
{
	int fd;
	int out;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0600);
	out = write(fd, text_content, _strlen(text_content));
	close(fd);
	if (out > 1)
		out = 0;
	return (out);
}
