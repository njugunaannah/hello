#include "main.h"

/**
 * get_history_file - get the path to the shell's history file
 * @info: a pointer to the info_t struct
 *
 * Return: a pointer to the path string, or NULL on error
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - write the contents of the history buffer to a file
 *
 * @info: a pointer to the struct containing information about the shell
 *
 * Return: 0 on success, or -1 if an error occurred
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads command history from file
 *
 * @info: A pointer to an info_t struct containing information about the shell
 *
 * Return: 0 on success, -1 on failure
 */

int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Builds a linked list of command history from the given
 *                      buffer.
 *
 * @info: Pointer to a struct containing information about the shell
 * environment.
 * @buf: Pointer to a buffer containing the command history.
 * @linecount: The number of lines in the command history buffer.
 *
 * Return: 0 on success, or -1 on failure.
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
	node = info->history;

	/* Add each character in `buf` to a new node in the history list */
	for (size_t i = 0; i < strlen(buf); i++)
	{
	add_node_end(&node, &buf[i], linecount);
	}

	if (!info->history)
	info->history = node;

	return (0);
}

/**
 * renumber_history - Renumber the history list after removing duplicates.
 * @info: Pointer to a struct containing information about the shell.
 *
 * Return: 0 on success, or -1 on error.
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i;

	for (i = 0; node; i++)
	{
	node->num = i;
	node = node->next;
	}

	return (info->histcount = i);
}
