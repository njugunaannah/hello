#include "main.h"

/**
 * _memset - Fill memory with a constant byte
 * @s: Pointer to the memory area
 * @b: Value to be set
 * @n: Number of bytes to be set
 *
 * Return: Pointer to the memory area
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; ++i)
	{
		s[i] = b;
	}

	return (s);
}

/**
 * ffree - Frees the memory allocated to a pointer and sets it to NULL
 * @pp: Pointer to the pointer to be freed
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	/* Free each memory block pointed to by pp */
	while (*pp != NULL)
	{
		free(*pp);
		pp++;
	}

	/* Free the original pointer */
	free(a);
}


/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
