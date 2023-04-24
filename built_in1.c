#include "main.h"

/**
 * _myhistory - Displays the command history
 * @info: A pointer to the info_t struct
 *
 * Return: Always returns 1
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - remove an alias from the alias list
 * @info: a pointer to the info struct
 * @str: the name of the alias to remove
 *
 * Return: 1 on success, 0 otherwise
 */

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Set the alias for the given info struct
 * @info: A pointer to the info_t struct
 * @str: A string representing the alias
 *
 * Return: 0 on success, -1 on failure
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints the alias contained in a node of a linked list.
 *
 * @node: A pointer to the node to print.
 *
 * Return: The number of characters printed.
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Performs a specific task on a given info_t struct.
 *
 * @info: Pointer to an info_t struct.
 *
 * Return: An integer value.
 */

int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
	node = info->alias;
	while (node)
	{
		print_alias(node);
		node = node->next;
	}
	return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
	p = _strchr(info->argv[i], '=');
	if (p)
	{
	set_alias(info, info->argv[i]);
	}
	else
	{
	node = node_starts_with(info->alias, info->argv[i], '=');
	for (; node != NULL; node = node->next)
		{
		print_alias(node);
		}
	}
}
	return (0);
}
