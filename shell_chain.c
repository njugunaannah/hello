#include "main.h"

/**
 * is_chain - Checks if a chain exists in the given buffer.
 * @info: Pointer to the info_t struct containing relevant information.
 * @buf: Pointer to the buffer to be checked.
 * @p: Pointer to the size_t variable representing the buffer size.
 *
 * Return: 1 if a chain is found, 0 otherwise.
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Check the chain for information.
 * @info: Pointer to the info_t structure.
 * @buf: Pointer to the buffer.
 * @p: Pointer to the size_t variable for tracking the position.
 * @i: Current index in the chain.
 * @len: Length of the chain.
 *
 * This function checks the chain for information by iterating through
 * the buffer and performing necessary operations based on the current
 * index and length of the chain.
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - Replaces alias information.
 * @info: Pointer to the info_t structure containing alias data.
 *
 * This function replaces the alias information in the given info_t structure.
 * It takes a pointer to the info_t structure
 * and modifies its alias information
 * based on some specific criteria.
 *
 * Return: None.
 */

int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in the info struct.
 * @info: Pointer to the info_t struct containing the variables.
 *
 * This function replaces variables in the info struct with their respective
 * values. It takes a pointer to the info struct and modifies its members.
 * The function does not return any value.
 * Return: 0
 */

int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces a string pointed to by old with a new string.
 * @old: Pointer to a pointer to the old string.
 * @new: Pointer to the new string.
 *
 * Return: The length of the replaced string, or -1 on failure.
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
