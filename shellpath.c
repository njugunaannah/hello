#include "main.h"

/**
* is_cmd - determines if a file is an executable command
* @info: the info struct
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int is_cmd(info_t *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* dup_chars - Copies characters from a string
* into a buffer between given start and stop indices.
*
* @pathstr: the string to copy from.
* @start: the index to start copying from.
* @stop: the index to stop copying at.
*
* Return: a pointer to the buffer containing the copied characters.
*/
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i, k;

for (i = start, k = 0; i < stop; i++)
{
if (pathstr[i] != ':')
{
buf[k] = pathstr[i];
k++;
}
}

buf[k] = '\0';

return (buf);
}



/**
* find_path - finds this cmd in the PATH string
* @info: the info struct
* @pathstr: the PATH string
* @cmd: the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
i}
