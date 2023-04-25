#include "main.h"

/**
* is_cmd - checks if the given path is a regular file
* @info: a pointer to an info_t struct
* @path: the path to check
*
* Return: 1 if the path is a regular file, 0 otherwise
*/
int is_cmd(info_t *info, char *path)
{
struct stat st;

(void)info;

if (!path || stat(path, &st))
{
return (0);
}

if (S_ISREG(st.st_mode))
{
return (1);
}

return (0);
}

/**
* dup_chars - copies characters from a string to a static buffer
* @pathstr: the string to copy characters from
* @start: the index to start copying characters from
* @stop: the index to stop copying characters at
*
* Return: a pointer to the static buffer containing the copied characters
*/
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i, k;

for (i = start, k = 0; i < stop; i++)
{
if (pathstr[i] != ':')
{
buf[k++] = pathstr[i];
}
}

buf[k] = '\0';

return (buf);
}

/**
* find_path - searches the PATH environment variable for a given command
* @info: a pointer to an info_t struct
* @pathstr: the PATH environment variable
* @cmd: the command to search for
*
* Return: a pointer to a string containing the full path to the command,
* or NULL if the command was not found
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i, curr_pos;
char *path;

if (!pathstr)
{
return (NULL);
}
if (_strlen(cmd) > 2 && starts_with(cmd, "./"))
{
if (is_cmd(info, cmd))
{
return (cmd);
}
}
for (i = 0, curr_pos = 0; ; i++)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
{
_strcat(path, cmd);
}
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(info, path))
{
return (path);
}
if (!pathstr[i])
{
break;
}
curr_pos = i + 1;
}
}
return (NULL);
}
