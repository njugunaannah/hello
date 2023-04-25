#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
/**
* *error_env - error message for env in get_env.
* @counter: data relevant (counter, arguments)
* @program_name: program name
* @arg: arg
* Return: error message.
*/

char *error_env(int counter, char *program_name, char *arg)
{
char *msg = "Unable to add/remove from environment\n";
char *error = malloc(strlen(program_name) + strlen(arg) + strlen(msg) + 20);
if (error == NULL)
{
return (NULL);
}
sprintf(error, "%s: %d: %s: %s", program_name, counter, arg, msg);
return (error);
}

/**
* error_path_126 - error message for path and failure denied permission.
* @counter: counter
* @program_name: program name
* @arg: arg
*
* Return: The error string.
*/

char *error_path_126(int counter, char *program_name, char *arg)
{
char *msg = "Permission denied\n";
char *error = malloc(strlen(program_name) + strlen(arg) + strlen(msg) + 20);
if (error == NULL)
{
return (NULL);
}
sprintf(error, "%s: %d: %s: %s", program_name, counter, arg, msg);
return (error);
}
