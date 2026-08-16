#include "hash_tables.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * key_index - gets an index of given key
 * @size: size of table
 * @key: key to use
 * Return: index
 */

unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}
