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
 * append_text_to_file - appends to a file
 * @filename: file to create
 * @text_content: text to write
 *
 * Return: 1 on success else -1
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int fd;
	int out;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_RDWR | O_APPEND);
	if (fd != -1)
		return(fd);

	if (text_content != NULL)
		out = write(fd, text_content, _strlen(text_content));
	
	out = 1;

	close(fd);
	if (out > 1)
		out = 1;
	return (out);
}
