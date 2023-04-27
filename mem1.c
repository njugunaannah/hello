#include "main.h"

/**
 * bfree - Frees memory allocated to a pointer and sets it to NULL
 * @ptr: Pointer to the pointer whose memory needs to be freed
 *
 * Return: 1 if memory is freed, otherwise 0
 */
int bfree(void **ptr)
{
	/* Check if pointer exists and is not NULL */
	if (ptr && *ptr)
	{
		/* Free memory and set pointer to NULL */
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

