#include <unistd.h>

/**
* _eputs - Prints a string to standard error.
* @s: The string to be printed.
* Return: void.
*/
void _eputs(const char *s)
{
while (*s)
{
write(STDERR_FILENO, s++, 1);
}
write(STDERR_FILENO, "\n", 1);
}

/**
* _eputchar - writes a character to the standard error output
* @c: the character to be written
*
* Return: void
*/
void _eputchar(int c)
{
write(STDERR_FILENO, &c, 1);
}

/**
* _putfd - writes a string to a file descriptor
* @fd: the file descriptor to write to
* @s: the string to write
*
* Return: void
*/
void _putfd(int fd, const char *s)
{
while (*s)
{
write(fd, s++, 1);
}
write(fd, "\n", 1);
}

/**
* _putsfd - writes a string to a file descriptor
*
* @fd: the file descriptor to write to
* @s: the string to write
*
* Return: none
*/
void _putsfd(int fd, const char *s)
{
_putfd(fd, s);
}

/**
* main - Entry point for the program
*
* Return: Always 0 (success)
*/

int main(void)
{
_eputs("Hello, world!");
_eputchar('A');
_putfd(STDOUT_FILENO, "Hello, stdout!");
_putsfd(STDOUT_FILENO, "Hello, stdout again!");
return (0);
}

