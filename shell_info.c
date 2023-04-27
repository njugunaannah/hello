#include "main.h"

/**
 * clear_info - Clears the contents of the given info struct
 *
 * This function sets all the fields of the info struct pointed to by the
 * `info` parameter to 0 or NULL, effectively clearing its contents.
 *
 * @info: Pointer to the info struct to be cleared
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Sets the values of the info_t
 * struct based on the command line arguments
 * @info: A pointer to the info_t struct
 * @av: A double pointer to the command line arguments
 *
 * This function takes in the command
 * line arguments as a double pointer, parses them,
 * and sets the corresponding values in
 * the info_t struct. The info_t struct is used
 * to store information about the program,
 * such as the file name and the number of
 * lines to be printed.
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
 * free_info - Frees memory allocated
 * for an info_t struct and its contents
 * @info: Pointer to the info_t struct to free
 * @all: Boolean flag indicating whether
 * to free all contents of info_t
 *
 * This function frees the memory allocated
 * for an info_t struct and its contents,
 * including the filename, file_contents,
 * and line_number fields. If the all flag
 * is set to a non-zero value, the contents
 * of the file_contents field will also be
 * freed. If the flag is set to zero, only
 * the struct and filename fields will be freed.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
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
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
