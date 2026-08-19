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
 * @letters: amounts of chars to read/write
 *
 * Return: 1 on success else -1
 */
int create_filecp(const char *filename, char *text_content, size_t letters)
{
	int fd;
	int out;

	if (letters == 0)
		letters = _strlen(text_content);

	fd = open(filename, O_WRONLY | O_APPEND);
	out = 0;
	out = write(fd, text_content, letters);

	if (close(fd) != 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %i\n", fd);
		exit(100);
	}

	return (out);
}

/**
 * read_textfilecp - writes chars from file
 * @filename: file to read from
 * @file_create: file to write to
 *
 * Return: 0 on error/no write, otherwise amount of chars written
 */
int read_textfilecp(const char *filename, char *file_create)
{
	int fd;
	int charp;
	int i;
	char buff[1024];

	if (filename == NULL)
		exit(98);
	fd = open(file_create, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_create);
		exit(99);
	}
	close(fd);
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
		create_filecp(file_create, buff, charp);
		i = 0;
		while (buff[i] != '\0')
		{
			buff[i] = '\0';
			i++;
		}
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
