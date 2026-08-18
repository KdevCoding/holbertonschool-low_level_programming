#include <stdio.h>
#include <stdlib.h>
#include "main.h"

ssize_t read_textfile(const char *filename, size_t letters)
{
    char *buff;
    ssize_t charp;

    if (filename == NULL || letters == 0)
        return (0);
    
    buff = malloc(sizeof(char) * letters + 1);
    if (buff == NULL)
        return (0);

    if (read(*filename, buff, letters) == -1)
        return (-1);
    
    charp = write(0, buff, letters);
    
    if (charp != (ssize_t)letters)
        charp = 0;
    return (charp);
}
