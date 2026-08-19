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
 * create_filecp - creates a file
 * @filename: file to create
 * @text_content: text to write
 *
 * Return: 1 on success else -1
 */
int create_filecp(const char *filename, char *text_content)
{
	int fd;
	int out;

	fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0664);
	out = 0;

	out = write(fd, text_content, _strlen(text_content));

	if (close(fd) != 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %i\n", fd);
		exit(100);
	}

	if (out < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", filename);
		exit(99);
	}

	return (out);
}

/**
 * read_textfilecp - writes chars from file
 * @filename: file to read from
 * @letters: amounts of chars to read/write
 * @buff: buffer to write to
 * Return: 0 on error/no write, otherwise amount of chars written
 */
int read_textfilecp(const char *filename, char *file_create)
{
	int fd;
	int charp;
	char buff[1024];

	if (filename == NULL)
		exit(98);

	fd = open(filename, O_RDONLY);
	charp = 1;
	while (charp != 0)
	{
		charp = read(fd, buff, (size_t)1023);
		if (charp == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", filename);
			exit(98);
		}

		create_filecp(file_create, buff);
	}
	if (close(fd) != 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %i\n", fd);
		exit(100);
	}
	return (charp);
}

/**
 * main - copy from one file to another
 * @ac: amount of args
 * @av: file_from file_to
 *
 * Return: always 0
 */
int main(int ac, char **av)
{

	if (ac != 3)
	{
		dprintf(2, "Usage: cp file_from file_to\n");
		exit(97);
	}

	read_textfilecp(av[1], av[2]);
	return (0);
}
