#include "main.h"

/**
 * add_node - Adds a new node to the beginning of a singly linked list.
 * @head: A pointer to the head of the list.
 * @str: The string to be added to the new node.
 * @num: The integer to be added to the new node.
 *
 * Return: If memory allocation fails, NULL. or a pointer to the new node.
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Add a new node at the end of a list_t list
 * @head: Pointer to a pointer to the head node of the list
 * @str: Pointer to the string to be stored in the new node
 * @num: Number to be stored in the new node
 *
 * Return: Pointer to the new node, or NULL on failure
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints all the strings in a linked list
 * @h: pointer to the head node of the list
 *
 * Return: the number of nodes in the list
 */

size_t print_list_str(const list_t *h)
{
	size_t i;

	for (i = 0; h != NULL; h = h->next, i++)
	{
	_puts(h->str ? h->str : "(nil)");
	_puts("\n");
	}

	return (i);
}

/**
 * delete_node_at_index - deletes the node at a given
 * position in a linked list
 * @head: pointer to pointer to the first node of the list
 * @index: index of the node to be deleted (starting from 0)
 *
 * Return: 1 if the node was successfully deleted, -1 otherwise
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees a linked list
 *
 * @head_ptr: A pointer to a pointer to the head node of the list
 *
 * This function frees all the nodes in a linked list by iterating through
 * the list and calling free() on each node. It also sets the head pointer
 * to NULL to indicate that the list is empty.
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
	return;

	head = *head_ptr;
	node = head;

	for (; node != NULL; node = next_node)
	{
	next_node = node->next;
	free(node->str);
	free(node);
	}

	*head_ptr = NULL;
}
