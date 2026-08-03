#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lists.h"

/**
 * _strlen - counts length of string
 * @s: var to count length
 *
 * Return: returns string length
 */

int _strlen(const char *s)
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
 * add_node_end - adds a new node at end of a linked list
 * @head: list start
 * @str: str to add at start of list
 *
 * Return: address of new element
 */

list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new;
	list_t *h;

	new = malloc(sizeof(list_t));
	if (new == NULL)
	{
		printf("Error\n");
		return (NULL);
	}

	new->str = strdup(str);
	if (new->str == NULL)
	{
		free(new);
		printf("Error\n");
		return (NULL);
	}

	new->len = _strlen(str);
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		h = *head;

		while (h->next != NULL)
		{
			h = h->next;
		}

		h->next = new;
	}
	return (new);
}
