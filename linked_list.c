#include "shell.h"

/**
 *add_node_end - adds a node to the end of the linked list
 *@head: pointer to head of linked list
 *@dir: directory for new node
 *Return: NULL/new node
 */

list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
  *free_list - frees a linked list
  *@head: head of list_t
 */

void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}

/**
 *add_alias_end - add a node at end of alias list
 *@head: a pointer to head of list
 *@name: new alias
 *@value: value of new alias
 *Return: NULL/ pointer to new node
 */

alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;


	if (!new_node)
		return (NULL);


	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);


	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;


	return (new_node);
}

/**
 *free_alias_list - frees alias list
 *@head: head of alias list
 */

void free_alias_list(alias_t *head)
{
	alias_t *next;


	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

