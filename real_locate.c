#include "main.h"

/**
* _memset - fills memory with a constant byte
* @s: pointer to the memory area to be filled
* @b: the character to fill the memory area with
* @n: the number of bytes to be filled
*
* Return: a pointer to the filled memory area
*/
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
{
s[i] = b;
}

return (s);
}

/**
* ffree - frees a double pointer and all of its elements
* @pp: the double pointer to be freed
*/
void ffree(char **pp)
{
char **a = pp;

if (!pp)
{
return;
}

while (*pp)
{
free(*pp);
pp++;
}

free(a);
}

/**
* _realloc - reallocates a memory block
* @ptr: the pointer to the previously allocated memory block
* @old_size: the size in bytes of the allocated space for ptr
* @new_size: the new size in bytes of the new memory block
*
* Return: a pointer to the new memory block, or NULL if failure
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;
unsigned int i;

if (!ptr)
{
return (malloc(new_size));
}

if (!new_size)
{
free(ptr);
return (NULL);
}

if (new_size == old_size)
{
return (ptr);
}

p = malloc(new_size);

if (!p)
{
return (NULL);
}

old_size = old_size < new_size ? old_size : new_size;

for (i = 0; i < old_size; i++)
{
p[i] = ((char *)ptr)[i];
}

free(ptr);

return (p);
}

