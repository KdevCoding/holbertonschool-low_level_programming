#include "hash_tables.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * hash_table_create - creates a hash_table
 * @size: size of table
 *
 * Return: hash table created
 */

hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *ht;
	unsigned long int i;

	ht = malloc(sizeof(hash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->array = malloc(sizeof(hash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	ht->size = size;

	while (i < size)
	{
		ht->array[i] = NULL;
		i++;
	}

	return (ht);
}
