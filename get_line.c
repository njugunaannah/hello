#include "main.h"

/**
 * input_buf - Reads input from the user and returns
 * a buffer with the input data
 * @info: A pointer to an info_t struct
 * containing information about the input source
 * @buf: A pointer to a pointer where the buffer will be stored
 * @len: A pointer to a size_t variable where
 * the length of the buffer will be stored
 *
 * Return: The number of bytes read from the
 * input source, or -1 if an error occurred
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Reads user input and stores it in info struct
 * @info: Pointer to the info struct
 *
 * Return: Number of bytes read, or -1 on failure
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - Read from a file descriptor
 * into a buffer and update the index
 *
 * This function reads up to the maximum
 * size of the buffer from the file
 * descriptor specified in the `info`
 * parameter, and stores the read data in the
 * buffer pointed to by `buf`. The current index into the buffer is stored in
 * the `i` parameter, and is updated to reflect the number of bytes read from
 * the file descriptor.
 *
 * @info: Pointer to a structure that contains the file descriptor to read from
 * @buf: Pointer to the buffer where the read data should be stored
 * @i: Pointer to the index into the buffer,
 * which is updated to reflect the number
 *     of bytes read
 *
 * Return: The number of bytes read from the file descriptor, or -1 on error
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Reads a line from input and stores it in a buffer
 * @info: Pointer to the info_t struct containing information about the input
 * @ptr: Pointer to a buffer to store the line read from input
 * @length: Pointer to a variable to
 * store the length of the line read from input
 *
 * Return: The number of characters read from input, or -1 on failure
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Handles the SIGINT signal.
 * @sig_num: The signal number (unused).
 *
 * This function is used as a handler for
 * the SIGINT signal. It is registered using
 * the signal() function, and is called
 * whenever the process receives the SIGINT signal.
 * The `sig_num` parameter is unused, and
 * is only included to satisfy the function signature
 * required by signal().
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
