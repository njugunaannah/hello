#include "main.h"

/**
 * is_chain - Determines if the current command is chained with the next
 * @info: shell information struct
 * @buf: current command buffer
 * @p: current index in buffer
 * Return: 1 if there is a chain, 0 otherwise
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
 * check_chain - Evaluates if the current command should chain to the next
 * @info: shell information struct
 * @buf: current command buffer
 * @p: current index in buffer
 * @i: current index in command buffer
 * @len: length of command buffer
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
 * replace_alias - Replaces the command with its alias, if one exists
 * @info: shell information struct
 * Return: 1 if successful, 0 otherwise
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
 * replace_vars - Replaces environment variables and other special characters
 * @info: shell information struct
 * Return: 1 if successful, 0 otherwise
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
_strdup(convert_number(info->pid, 10, 0)));
continue;
}
node = node_starts_with(info->env, info->argv[i] + 1, '=');
if (!node)
continue;
replace_string(&(info->argv[i]), _strdup(node->str + _strlen(info->argv[i])));
if (!info->argv[i])
return (0);
}
return (1);
}
/**

execute_cmd - Executes the current command

@info: shell information struct

Return: 1 if successful, 0 otherwise
*/
int execute_cmd(info_t *info)
{
int status;

if (replace_alias(info) == 0)
return (0);

if (replace_vars(info) == 0)
return (0);
if (_strcmp(info->argv[0], "exit") == 0)
exit_shell(info, NULL);

if (_strcmp(info->argv[0], "cd") == 0)
return (change_dir(info));

status = execute(info);

return (status);
}
