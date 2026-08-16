#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * hash_table_get - retrieves value of node with given key
 * @ht: list start
 * @key: key to node
 *
 * Return: value
 */

char *hash_table_get(const hash_table_t *ht, const char *key)
{
	unsigned long int index;
	hash_node_t *arri;

	if (key == NULL || ht == NULL)
		return (0);
	index = key_index((unsigned char *)key, ht->size);
	arri = ht->array[index];


	while (arri != NULL)
	{
		if (strcmp(arri->key, key) == 0)
			break;
		arri = arri->next;
	}

	if (arri == NULL)
	{
		return (NULL);
	}
	else
	{
		return (arri->value);
	}
}
