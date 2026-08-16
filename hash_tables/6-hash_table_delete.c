#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * free_list - free linked list
 * @head: list
 *
 *
 *
 */

void free_list(hash_node_t *head)
{
	hash_node_t *next;

	if (head == NULL)
		return;

	while (head->next != NULL)
	{
		free(head->key);
		free(head->value);
		next = head->next;
		free(head);
		head = next;
	}

	free(head->key);
	free(head->value);
	free(head);
}

/**
 * hash_table_delete - deletes a hash table
 * @ht: list start
 *
 *
 * Return: value
 */

void hash_table_delete(hash_table_t *ht)
{
	unsigned long int index;

	index = 0;
	while (index < ht->size)
	{
		free_list(ht->array[index]);
		index++;
	}
	free(ht->array);
	free(ht);
}
