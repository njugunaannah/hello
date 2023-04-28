#include "main.h"


/**
* duplicateArray - creates a new array
* with the contents of a previous array
* @previousArray: pointer to the previous array
* @createdArraySize: size of the new array to be created
* Return: pointer to the newly created array
* with the same contents as the previous array
*/
char **duplicateArray(char **previousArray, int createdArraySize)
{
char **createdArray = NULL;
char **arrayPointer;
/* Allocate memory for the new array */
createdArray = malloc(sizeof(char **) * createdArraySize);
/* Set arrayPointer to point to first element of the new array*/
arrayPointer = createdArray;
/* Loop through the previous array and copy element to new array*/
while (*previousArray != NULL)
{
/* Copy string pointed to by previousArray, store pointer in arrayPointer*/
*arrayPointer = copyString(*previousArray);
/* Move to the next element in each array */
arrayPointer++;
previousArray++;
}
/* Set the last element of the new array to NULL */
*arrayPointer = NULL;
/* Return a pointer to the newly created array */
return (createdArray);
}

/**
* releaseArray - function to free up the memory
* allocated to an array of strings
* @arguements: the array of strings to be released
* This function takes an array of strings and
* frees up the memory allocated to each string
* in the array and then frees up the
* memory allocated to the array itself.
* Return: POSITIVE (1) on success
*/

int releaseArray(char **arguements)
{
char **pointer = arguements;
/* loop through the array until NULL is reached */
while (*pointer != NULL)
{
/* free the memory allocated to the string */
free(*pointer);
/* move the pointer to the next string in the array */
pointer++;
}
/* free up the memory allocated to the array */
free(arguements);
/* return POSITIVE (1) to indicate success */
return (POSITIVE);
}
/**
* findArrayElement - search for a string
* element in an array of strings
* @array: pointer to an array of strings
* @itemName: string to search for
* Return: a pointer to the first matching
* string in the array or NULL if not found
*/
char *findArrayElement(char **array, char itemName)
{
/* loop through the array until the end is reached */
while (array != NULL)
{
/* if the current string matches the itemName, return it */
if (compareString(*array, itemName, PREFIX) == POSITIVE)
return (*array);
/* move to the next element in the array */
array++;
}
/* if no match is found, return NULL */
return (NULL);
}
/**
* createArray - function that creates an
* array of strings from a given string
* @string: the input string
* @endOfListEntryChar: the character that
* marks the end of a list entry
* @ifSemiColonPointer: pointer to the next
* position after a semicolon in the input string
* Return: a pointer to the array of strings
*/
char **createArray(char *string, char endOfListEntryChar,
char **ifSemiColonPointer)
{
char *stringPointer = string;
unsigned int index = 2;
char **array = NULL;
/* loop through the string to count the number of list entries */
while (*stringPointer != '\0')
{
if (*stringPointer == ';')
break;
if (*stringPointer == endOfListEntryChar && *(stringPointer + 1) != '\0')
index++;
stringPointer++;
}
/* allocate memory for the array of strings */
array = malloc(index *sizeof(char **));
if (array == NULL)
exit(EXIT_FAILURE);
/* assign the first element of the array to the input string */
array[0] = string;
stringPointer = string;
index = 1;
/* loop through the string to extract the list entries, populate the array*/
while (*stringPointer != '\0')
{
if (stringPointer == endOfListEntryChar)
{
*stringPointer = '\0';
stringPointer++;
if (stringPointer == ';')
{
/ end of list reached /
array[index] = NULL;
if ((stringPointer + 1) != '\0' && *(stringPointer + 2) != '\0')
*ifSemiColonPointer = stringPointer + 2;
break;
}
if (stringPointer != '\0')
}
array[index] = stringPointer;
index++;
}
}
stringPointer++;
}
array[index] = NULL;
return (array);
}
