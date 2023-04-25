#include "main.h"

/**
* path_len - calculates the length of a string until the first colon
* @path: the path string
* Return: the length of the string until the first colon, or the length of the
* entire string if there is no colon.
*/
int path_len(char *path)
{
int i;
if (!path)
return (0);
for (i = 0; *path; i++)
{
if (*path == ':')
i++;
path++;
}
return (i);
}
/**
* free_arr - Frees an array of strings
* @arr: The array to be freed
* Return: Nothing
*/
void free_arr(char **arr)
{
int i;
if (!arr)
return;
for (i = 0; arr[i]; i++)
free(arr[i]);
free(arr);
}
/**
* is_delim - checks if a character is a delimiter
* @c: character to check
* @delim: string containing delimiter characters
* Return: 1 if c is a delimiter, 0 otherwise
*/
int is_delim(char c, char *delim)
{
while (*delim)
{
if (c == *delim)
return (1);
delim++;
}
return (0);
}
/**
* is_cmd - Check if cmd is a command
* @info: Pointer to info_t struct
* @cmd: The command to check
* Return: 1 if command exists, 0 otherwise
*/
int is_cmd(info_t *info, char *cmd)
{
char **path_arr;
char *tmp_path = NULL;
int i;
if (!cmd || cmd[0] == '/')
return (1);
path_arr = tokenize_path(_getenv(info, "PATH="));
if (!path_arr)
return (0);
for (i = 0; path_arr[i]; i++)
{
tmp_path = _strcat(path_arr[i], "/");
tmp_path = _strcat(tmp_path, cmd);
if (access(tmp_path, X_OK) == 0)
break;
free(tmp_path);
tmp_path = NULL;
}
free_arr(path_arr);
if (tmp_path)
{
free(tmp_path);
return (1);
}
return (0);
}
