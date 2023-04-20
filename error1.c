#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* strcat_cd - function that concatenates the message for cd error
*
* @datash: data relevant (directory)
* @msg: message to print
* @error: output message
* @ver_str: counter lines
* Return: error message
*/
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
char *illegal_flag;
int size = strlen(datash->av[0]) + strlen(msg) + strlen(datash->args[0])
	+ strlen(ver_str) + strlen(datash->args[1]) + 6;

error = (char *)malloc(sizeof(char) * size);
if (!error)
return (NULL);

snprintf(error, size, "%s: %s: %s%s", datash->av[0], ver_str, datash->args[0],
		msg);

if (datash->args[1][0] == '-')
{
illegal_flag = (char *)malloc(sizeof(char) * 4);
if (!illegal_flag)
{
free(error);
return (NULL);
}
snprintf(illegal_flag, 4, "-%c", datash->args[1][1]);
strcat(error, illegal_flag);
free(illegal_flag);
}
else
strcat(error, datash->args[1]);

strcat(error, "\n");
return (error);
}

/**
* error_get_cd - error message for cd command in get_cd
* @datash: data relevant (directory)
* Return: Error message
*/

char *error_get_cd(data_shell *datash)
{
char *msg, *error, *ver_str;
int len_id, size;

ver_str = aux_itoa(datash->counter);

if (datash->args[1][0] == '-')
{
msg = ": Illegal option ";
len_id = 2;
}
else
{
msg = ": can't cd to ";
len_id = strlen(datash->args[1]);
}

size = strlen(datash->av[0]) + strlen(msg) + strlen(datash->args[0])
	+ strlen(ver_str) + len_id + 5;

error = (char *)malloc(sizeof(char) * size);
if (!error)
{
free(ver_str);
return (NULL);
}

error = strcat_cd(datash, msg, error, ver_str);

free(ver_str);

return (error);
}

/**
* error_not_found - generic error message for command not found
* @datash: data relevant (counter, arguments)
* Return: Error message
*/

char *error_not_found(data_shell *datash)
{
char *error, *ver_str;
int size;

ver_str = aux_itoa(datash->counter);

size = strlen(datash->av[0]) + strlen(ver_str) + strlen(datash->args[0]) + 16;

error = (char *)malloc(sizeof(char) * size);
if (!error)
{
free(ver_str);
return (NULL);
}

snprintf(error, size, "%s: %s: %s: not found\n", datash->av[0], ver_str,
		datash->args[0]);

free(ver_str);
return (error);
}

/**
* error_exit_shell - generic error message for exit in get_exit
* @datash: data relevant (counter, arguments)
*
* Return: Error message
*/

char *error_exit_shell(data_shell *datash)
{
char *error, *ver_str;
int size;

ver_str = aux_itoa(datash->counter);

size = strlen(datash->av[0]) + strlen(ver_str) + strlen(datash->args[0])
	+ strlen(datash->args[1]) + 23;

error = (char *)malloc(sizeof(char) * size);

if (!error)
{
free(ver_str);
return (NULL);
}
snprintf(error, size, "%s: %s: %s: numeric argument required\n", datash->av[0],
		ver_str, datash->args[0]);

free(ver_str);
return (error);

}

/**
* error_many_args - generic error message for command not found
* @datash: data relevant (counter, arguments)
* Return: Error message
*/

char *error_many_args(data_shell *datash)
{
char *error, *ver_str;
int size;
ver_str = aux_itoa(datash->counter);

size = strlen(datash->av[0]) + strlen(ver_str) + strlen(datash->args[0]) + 23;

error = (char *)malloc(sizeof(char) * size);
if (!error)
{
free(ver_str);
return (NULL);
}

snprintf(error, size, "%s: %s: too many arguments\n", datash->av[0], ver_str);

free(ver_str);
return (error);

}
