#include "main.h"

/**
 * clear_info - Frees the memory used by `info` and sets its members to zero
 * @info: Pointer to the `info_t` structure to be cleared
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes the fields of the `info` struct with the values
 * provided in the `av` argument vector.
 *
 * @info: Pointer to the `info` struct to be initialized.
 * @av: Argument vector containing the command line arguments.
 */

void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}


/**
 * free_info - frees the memory allocated for info struct
 *
 * @info: pointer to the info struct to be freed
 * @all: flag indicating whether to free all fields or just some
 */
void free_info(info_t *info, int all)
{
	int i;

	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
	/* free all fields of the info struct */
	if (!info->cmd_buf)
	free(info->arg);
	if (info->env)
	free_list(&(info->env));
	if (info->history)
	free_list(&(info->history));
	if (info->alias)
	free_list(&(info->alias));
	ffree(info->environ);
	info->environ = NULL;

	for (i = 0; info->cmd_buf[i]; i++)
	bfree((void **)(&info->cmd_buf[i]));
	bfree((void **)info->cmd_buf);

	if (info->readfd > 2)
	close(info->readfd);
	_putchar(BUF_FLUSH);
	}
}
