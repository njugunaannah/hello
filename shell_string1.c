#include "main.h"

/**
* _strcpy - copies the string pointed to by src to the buffer
*           pointed to by dest.
* @dest: buffer to copy string to
* @src: string to be copied
*
* Return: the pointer to dest
*/

char *_strcpy(char *dest, char *src)
{
	int i;

if (dest == src || src == 0)
return (dest);
for (i = 0; src[i] != '\0'; i++)
dest[i] = src[i];
return (dest);
}

/**
* _strdup - Returns a pointer to a newly allocated space in memory,
* which contains a copy of the string given as a parameter.
*
* @str: The string to copy.
*
* Return: If str is NULL or insufficient memory is available, returns NULL.
* Otherwise, returns a pointer to the duplicated string.
*/

char *_strdup(const char *str)
{
int length = 0;
char *ret;
int i;
const char *c;

if (str == NULL)
return (NULL);
for (c = str; *c != '\0'; c++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (i = 0; i <= length; i++)
ret[i] = str[i];
return (ret);
}

/**
* _puts - Prints a string to stdout.
*
* @str: A pointer to the string to be printed.
*
* Return: void
*/
void _puts(char *str)
{
	int i;

if (!str)
return;
for (i = 0; str[i] != '\0'; i++)
_putchar(str[i]);
}

/**
* _putchar - writes the character c to stdout
*
* @c: the character to print
*
* Return: On success 1, on error, -1 is returned,
*         and errno is set appropriately.
*/

int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

