
#include "main.h"


/**
* list_len - Counts the number of elements in a linked list.
* @h: Head of the linked list.
* Return: The number of nodes.
*/
size_t list_len(const list_t *h)
{
size_t i = 0;

while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
* list_to_strings - Allocates memory for an array of strings,
* and copies the string data of each node of a linked list.
* @head: Head of the linked list.
* Return: The array of strings or NULL if memory allocation fails.
*/
char **list_to_strings(list_t *head)
{
list_t *node = head;
size_t i = list_len(head), j;
char **strs;
char *str;

if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}

str = _strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}


/**
* print_list - Prints all the nodes of a linked list.
* @h: Pointer to the head of the linked list.
* Return: The number of nodes in the linked list.
*/
size_t print_list(const list_t *h)
{
size_t i = 0;

while (h)
{
_puts(convert_number(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
* node_starts_with - Searches for the first node that starts with a prefix and
* contains a specific character.
* @node: A node of the linked list.
* @prefix: Character string to match the start of the node's string data.
* @c: A character to match inside the node's string data.
* Return: The first node that matches both the prefix and character or NULL if
* no node matches.
*/
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
char *p = NULL;

while (node)
{
p = starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
* get_node_index - Returns the node's index in a linked list.
* @head: A pointer to the head of the linked list.
* @node: A pointer to the node whose index is to be found.
* Return: Index of the node in the linked list or -1 if the node is not found
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t i = 0;

while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}
