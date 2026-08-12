#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lists.h"

/**
 * add_node - adds a new node at begining of a linked list
 * @head: list start
 * @str: str to add at start of list
 *
 * Return: address of new element
 */

dlistint_t *add_dnodeint(dlistint_t **head, const int n)
{
	dlistint_t *new;

	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
	{
		printf("Error\n");
		return (NULL);
	}

	new->n = n;
	new->prev = NULL;
	new->next = *head;

	*head = new;
	if (new->next != NULL)
	{
		new = new->next;
		new->prev = *head;
	}
	return (*head);
}
