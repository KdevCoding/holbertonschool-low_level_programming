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
		printf("Error\n");
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
	hash_node_t *node;

	if (key == NULL)
		return (0);
	index = key_index((unsigned char *)key, ht->size);
	arri = ht->array[index];

	node = arri;
	while (node != NULL)
	{
		if (node->key == key)
			break;
		node = node->next;
	}

	if (node == NULL)
	{
		node = add_node(arri, key, value);
	}
	else
		node->value = strdup(value);

	if (node == NULL)
		return (0);

	return (1);
}
