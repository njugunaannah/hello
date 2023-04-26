#include "main.h"

/**
* strtow - Splits a string into words using a delimiter string
*
* @str: String to split
* @d: Delimiter string
*
* Return: Pointer to an array of strings (words) on success, or NULL on failure
*/

char **strtow(char *str, char *d)
{
int i, j, k, m, numwords = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (i = 0; str[i] != '\0'; i++)
if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
numwords++;

if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (is_delim(str[i], d))
i++;
k = 0;
while (!is_delim(str[i + k], d) && str[i + k])
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}

/**
* **strtow2 - splits a string into words
* @str: the input string
* @d: the delimeter
* Return: a pointer to an array of strings, or NULL on failure
*/
#include <stdlib.h>
#include <string.h>

char **strtow2(char *str, char d)
{
	if (!str || !*str)
		return (NULL);

	int i;
	int numwords = 1;

	for (i = 0; str[i]; i++)
	if (str[i] == d)
		numwords++;

	char **s = malloc((numwords + 1) * sizeof(char *));

	if (!s)
		return (NULL);

	char *token = strtok(str, &d);

	for (i = 0; token; i++)
	{
	s[i] = strdup(token);
	if (!s[i])
	{
	for (int j = 0; j < i; j++)
		free(s[j]);
	free(s);
	return (NULL);
	}
	token = strtok(NULL, &d);
	}
	s[i] = NULL;
	return (s);
}
