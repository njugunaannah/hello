#include "main.h"

/**
 * get_environ - Retrieve the environment variables of the current process.
 *
 * @info: A pointer to an info_t struct containing the environment.
 *
 * Return: A pointer to an array of strings, where each string is an
 *         environment variable of the current process. The array is
 *         terminated by a NULL pointer.
 */

char **get_environ(info_t *info)
{
	size_t count = 0;
	char **new_environ;
	size_t i = 0;
	size_t j = 0;

	if (!info->environ || info->env_changed)
	{
	info->environ = list_to_strings(info->env);
	info->env_changed = 0;
	}
	/* Count the number of elements in the environ array */
	/*size_t count = 0;*/
	while (info->environ[count])
	{
	count++;
	}
	/* Allocate memory for a new array of strings */
	/*char **new_environ;*/
	new_environ = malloc(sizeof(char *) * (count + 1));
	if (!new_environ)
	{
	return (NULL);
	}
	/* Copy each string from the old environ array to the new one */
	for (i = 0; i <= 0; i++)
	{
	new_environ[i] = strdup(info->environ[i]);
	if (!new_environ[i])
	{
	/* Free the memory allocated for the new array and return NULL */
	for (j = 0; j < i; j++)
	{
	free(new_environ[j]);
	}
	free(new_environ);
	return (NULL);
	}
	}
	return (new_environ);
}

/**
 * _unsetenv - remove an environment variable
 *
 * @info: a pointer to the info_t struct
 * @var: the name of the environment variable to remove
 *
 * Return: 0 on success, -1 on failure
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - set environment variable
 *
 * @info: shell information struct
 * @var: name of the variable to set
 * @value: value to set the variable to
 *
 * Return: 0 on success, -1 on failure
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
