#include "main.h"

/**
 * _strlen - Computes the length of a string.
 *
 * @s: Pointer to the string to compute the length of.
 *
 * Return: The length of the string.
 */

int _strlen(char *s)
{
	int i;

	if (!s)
		return (0);

	for (i = 0; s[i]; i++)
		;
	return (i);
}

/**
 * _strcmp - compare two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: 0 if s1 and s2 are equal, negative integer if s1 is less than s2,
 *         positive integer if s1 is greater than s2.
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	if (s1[i] == s2[i])
		return (0);
	else
		return (s1[i] < s2[i] ? -1 : 1);
}

/**
 * starts_with - checks if the string haystack starts with the string needle
 *
 * @haystack: the string to check
 * @needle: the string to look for at the beginning of haystack
 *
 * Return: a pointer to the beginning of haystack if it starts with needle,
 *         NULL otherwise
 */
char *starts_with(const char *haystack, const char *needle)
{
	int i;

	for (i = 0; needle[i]; i++)
	{
		if (needle[i] != haystack[i])
			return (NULL);
	}
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the resulting string.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;
	int i, j;

	for (i = 0; dest[i]; i++)
		;
	for (j = 0; src[j]; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';

	return (ret);
}

