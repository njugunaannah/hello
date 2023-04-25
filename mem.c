/**

bfree - frees memory allocated using malloc
@ptr: pointer to pointer to the allocated memory
Return: 1 if memory was freed, 0 otherwise
*/
int bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
