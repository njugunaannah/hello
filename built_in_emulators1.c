#include "main.h"

/**
 * _myhistory - Retrieves the history information.
 *
 * @info: Pointer to the info_t struct containing relevant data.
 *
 * Return: Integer value representing the status of the operation.
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Unset an alias from the info struct.
 * @info: Pointer to the info_t struct containing alias information.
 * @str: String representing the alias to be unset.
 *
 * Return: void
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
 * set_alias - Set an alias in the info_t structure.
 * @info: Pointer to the info_t structure.
 * @str: String containing the alias to be set.
 *
 * Description: This function sets an alias in the info_t structure. It takes
 * a pointer to the info_t structure and a string containing the alias in the
 * format "alias=value".
 *
 * Return: 0 if the alias is set successfully, 1 otherwise.
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
 * print_alias - Prints the contents of a given node in a list
 * @node: Pointer to the node to be printed
 *
 * Return: Integer indicating the success (1) or failure (0) of the operation
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
 * _myalias - A function that performs a specific task.
 *
 * @info: A pointer to an info_t struct containing relevant information.
 * A string parameter.
 *
 * Return: An integer value representing the result of the operation.
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
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
