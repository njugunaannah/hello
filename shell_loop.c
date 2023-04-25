/* Function to execute shell commands */
#include "main.h"

/**
* hsh - function to execute shell commands
* @info: structure containing shell information
* @av: pointer to array of arguments
* Return: returns the value of find_builtin
*/
int hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clear_info(info);
if (interactive(info))
_puts("$ ");

_eputchar(BUF_FLUSH);
r = get_input(info);

if (r != -1)
{
set_info(info, av);
builtin_ret = find_builtin(info);

if (builtin_ret == -1)
find_cmd(info);
}
else if (interactive(info))
_putchar('\n');

free_info(info, 0);
}

write_history(info);
free_info(info, 1);

if (!interactive(info) && info->status)
exit(info->status);

if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}

return (builtin_ret);
}

/**
* find_builtin - function to find if a command is a builtin command
* @info: structure containing shell information
* Return: returns the value of built_in_ret
*/
int find_builtin(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}

return (built_in_ret);
}

/**
* find_cmd - function to find a command
* @info: structure containing shell information
* Return: void
*/
void find_cmd(info_t *info)
{
char *path = NULL;
int i, k;

info->path = info->argv[0];

if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!is_delim(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((interactive(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}
/**
* find_path - finds the full path to a command in the PATH environment variable
* @info: pointer to struct containing command line arguments and options
* @path_str: string containing the PATH environment variable
* @cmd: the command to search for in the PATH
* Return: pointer to string containing the full path to the command, or NULL if
* the command is not found in the PATH
*/
char *find_path(info_t *info, char *path_str, char *cmd)
{
char **path_arr;
char *tmp_path = NULL;
int i;
if (!cmd || cmd[0] == '/')
return (cmd);
path_arr = tokenize_path(path_str);
if (!path_arr)
return (NULL);
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
return (tmp_path);
}
/**
* tokenize_path - Splits a string into tokens by a delimiter character
* @path: the string to tokenize
* Return: A pointer to an array of tokens, or NULL on failure
*/
char **tokenize_path(char *path)
{
char **path_arr;
int i;
if (!path)
return (NULL);
path_arr = malloc(sizeof(char *) * (path_len(path) + 1));
if (!path_arr)
return (NULL);
for (i = 0; *path; i++)
{
if (*path == ':')
{
path_arr[i++] = strdup("");
if (!path_arr[i - 1])
{
free_arr(path_arr);
return (NULL);
}
path++;
}
path_arr[i] = _strchr(path, ':');
if (path_arr[i])
*(path_arr[i]++) = '\0';
else
path_arr[i] = "";
}
path_arr[i] = NULL;
return (path_arr);
}
