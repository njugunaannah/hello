#include "main.h"

/**
 * _eputs - Prints a string to the standard error output
 * @str: Pointer to the string to be printed
 *
 * Description:
 * The _eputs function is used to print a string to the standard error output.
 * It takes a pointer to the string to be printed as a parameter.
 *
 * Return: None
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes a character to the standard error
 * @c: The character to be written
 *
 * Return: On success, the character written. On failure, -1.
 */

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Writes a character to a file descriptor
 * @c: The character to be written
 * @fd: The file descriptor to write to
 *
 * Return: On success, the number of bytes written. On error, -1 is returned.
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}


/**
 * _putsfd - Writes a string to a file descriptor
 * @str: Pointer to the string to be written
 * @fd: File descriptor to write the string to
 *
 * Return: Number of characters written
 */
int _putsfd(char *str, int fd)
{
	int i;

	if (!str)
	return (0);
	for (i = 0; str[i] != '\0'; i++)
	{
	i += _putfd(str[i], fd);
	}

	return (i);
}
