#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "main.h"

/**
 * read_textfile - writes chars from file
 * @filename: file to read from
 * @letters: amounts of chars to read/write
 *
 * Return: 0 on error/no write, otherwise amount of chars written
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buff;
	int fd;
	ssize_t charp;

	if (filename == NULL || letters == 0)
		return (0);

	buff = malloc(sizeof(char) * letters + 1);
	if (buff == NULL)
		return (0);

	fd = open(filename, O_RDONLY);
	charp = read(fd, buff, letters);
	if (charp == -1)
		return (0);
	else if (charp > 0)
		letters = charp;
	close(fd);
	charp = write(STDOUT_FILENO, buff, letters);

	if (charp != (ssize_t)letters)
		charp = 0;
	free(buff);
	return (charp);
}
