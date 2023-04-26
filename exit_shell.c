#include "main.h"

/**
 * _strncpy - copies up to n bytes of the src string to dest
 * @dest: the destination string
 * @src: the source string
 * @n: the maximum number of bytes to copy
 *
 * Return: a pointer to the resulting string dest
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates n characters from src to the end of dest.
 *
 * @dest: A pointer to the destination string.
 * @src: A pointer to the source string.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: A pointer to the resulting string dest.
 */

char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	char *s = dest;
<<<<<<< HEAD

	for (dest[i] != '\0' i++);
=======
	int j;
	for (i = 0; dest[i] != '\0'; i++)
>>>>>>> 4ba0c015b7e7c79456ffdd652e38651a92bcdf01
	{
		/* empty body, loop used to find end of dest string */
	}

	for (j = 0; src[j] != '\0' && j < n; j++, i++)
	{
		dest[i] = src[j];
	}

	if (j < n)
	{
		dest[i] = '\0';
	}

	return (s);
}

/**
 * _strchr - locate a character in a string
 * @s: pointer to the string
 * @c: character to search for
 *
 * Return: pointer to the first occurrence
 * of the character, or NULL if not found
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
