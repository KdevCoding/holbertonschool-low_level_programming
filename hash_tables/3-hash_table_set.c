#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * add_node - adds a new node at begining of a linked list
 * @head: list start
 * @key: key to node
 * @value: value to node
 * Return: address of new element
 */

hash_node_t *add_node(hash_node_t *head, const char *key, const char *value)
{
	hash_node_t *new;

	new = malloc(sizeof(hash_node_t));
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}

	new->key = strdup(key);
	new->value = strdup(value);
	new->next = head;

	head = new;

	return (head);
}

/**
 * hash_table_set - adds an element to has table
 * @ht: hash table
 * @key: key to use
 * @value: value to insert
 * Return: 1 if success else 0
 */

int hash_table_set(hash_table_t *ht, const char *key, const char *value)
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
		ht->array[index] = add_node(ht->array[index], key, value);
	}
	else
	{
		arri->value = strdup(value);
	}

	if (ht->array[index] == NULL)
		return (0);
	return (1);
}
