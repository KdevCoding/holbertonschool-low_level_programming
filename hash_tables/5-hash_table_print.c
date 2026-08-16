#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * hash_table_print - prints hash table
 * @ht: list start
 *
 *
 * Return: value
 */

void hash_table_print(const hash_table_t *ht)
{
	unsigned long int index;
	unsigned int first;
	hash_node_t *arri;

	first = 1;
	index = 0;
	printf("{");
	while (index < ht->size)
	{
		arri = ht->array[index];
		while (arri != NULL)
		{
			if (!first)
				printf(", ");
			printf("'%s': '%s'", arri->key, arri->value);
			first = 0;
			arri = arri->next;
		}
		index++;
	}
	printf("}\n");
}
