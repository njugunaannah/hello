#include "main.h"

/**
 * hsh - main function of the shell program
 * @info: pointer to struct containing information about the shell
 * @av: double pointer to array of strings containing command line arguments
 *
 * Return: returns the exit status of the shell
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	/* loop until there is an error or builtin returns -2 */
	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info); /* clear the information in the info struct */
		if (interactive(info)) /* if shell is in interactive mode */
			_puts("$ "); /* print prompt */
		_eputchar(BUF_FLUSH); /* flush the output buffer */
		r = get_input(info); /* read input from user */
		if (r != -1)
		{
			set_info(info, av); /* set info struct with input */
			builtin_ret = find_builtin(info); /* check for built-in commands */
			if (builtin_ret == -1) /* if command is not a built-in */
				find_cmd(info); /* search for executable in PATH */
		}
		else if (interactive(info)) /* if shell is in interactive mode and there is an error */
			_putchar('\n'); /* print newline character */
		free_info(info, 0); /* free info struct */
	}
	write_history(info); /* write history to file */
	free_info(info, 1); /* free info struct */
	if (!interactive(info) && info->status) /* if shell is not in interactive mode and there is an error */
		exit(info->status); /* exit with status */
	if (builtin_ret == -2) /* if user types exit */
	{
		if (info->err_num == -1) /* if there is an error */
			exit(info->status); /* exit with status */
		exit(info->err_num); /* exit with error number */
	}
	return (builtin_ret); /* return the exit status of the shell */
}

/**
 * find_builtin - checks if command is a built-in command
 * @info: pointer to struct containing information about the shell
 *
 * Return: returns the exit status of the built-in command or -1 if not found
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

	for (i = 0; builtintbl[i].type; i++) /* loop through the built-in command table */
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0) /* if the command matches a built-in */
		{
			info->line_count++; /* increment the line count */
			built_in_ret = builtintbl[i].func(info); /* execute the built-in command function */
			break; /* break out of the loop */
		}
	return (built_in_ret); /* return the exit status of the built-in command */
}

/**
 * find_cmd - searches for executable in PATH
 * @info: pointer to struct containing information about the shell
 *
 * Return: returns nothing
 */
void find_cmd(info_t
(info)
{
char **paths, *path, *cmd;
int i, status = 0;
path = _getenv("PATH", info->env); /* get PATH environment variable */
if (!path) /* if PATH environment variable does not exist */
{
	info->err_num = ENOCMD;
	handle_errors(info);
	return;
}
paths = tokenize(path, ":"); /* tokenize PATH into individual paths */
cmd = info->argv[0]; /* get the command name */
for (i = 0; paths[i]; i++) /* loop through each path in PATH */
{
	status = check_path(paths[i], cmd, info); /* check if executable exists in path */
	if (status == 0) /* if executable exists */
		break; /* break out of the loop */
}
free(paths); /* free the memory allocated for paths */
if (status != 0) /* if executable does not exist */
{
	info->err_num = ENOCMD;
	handle_errors(info);
}
}

/**

check_path - checks if executable exists in specified path

@path: path to search for executable

@cmd: command to search for

@info: pointer to struct containing information about the shell

Return: returns 0 if executable exists, 1 if not
*/
int check_path(char *path, char *cmd, info_t *info)
{
char *fullpath;
int status;

fullpath = build_path(path, cmd); /* build full path to executable /
status = access(fullpath, X_OK); / check if file is executable /
if (status == 0) / if file is executable /
{
info->argv[0] = fullpath; / set full path as command /
exec_cmd(info); / execute command /
free(fullpath); / free the memory allocated for fullpath /
return (0); / return success /
}
free(fullpath); / free the memory allocated for fullpath /
return (1); / return failure */
}

/**

build_path - builds full path to executable

@path: path to executable

@cmd: command to execute

Return: returns pointer to full path
*/
char *build_path(char *path, char *cmd)
{
char *fullpath;

fullpath = malloc(_strlen(path) + _strlen(cmd) + 2); /* allocate memory for full path /
if (!fullpath) / if malloc fails /
exit(EXIT_FAILURE); / exit with failure status /
_memset(fullpath, 0, _strlen(path) + _strlen(cmd) + 2); / set fullpath to null /
_strcpy(fullpath, path); / copy path into fullpath /
_strcat(fullpath, "/"); / concatenate / to fullpath /
_strcat(fullpath, cmd); / concatenate cmd to fullpath /
return (fullpath); / return full path */
}

/**

find_cmd - searches for executable in PATH

@info: pointer to struct containing information about the shell

Return: returns nothing
*/
void find_cmd(info_t *info)
{
char *path, *token, *cmd;
struct stat st;
int i;

path = _getenv("PATH", info->env); /* get PATH environment variable /
token = _strtok(path, ":"); / tokenize PATH variable /
while (token != NULL) / loop through each directory in PATH /
{
cmd = _strcat(token, "/", info->argv[0]); / concatenate directory with command /
if (stat(cmd, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) / check if file is executable /
{
info->line_count++; / increment line count /
create_child(info, cmd); / create child process to execute command /
free(path);
free(cmd);
return;
}
free(cmd);
token = _strtok(NULL, ":"); / get next token in PATH variable /
}
free(path);
/ command not found /
info->status = 127; / set status to 127 /
_puts_err(info->argv[0]); / print error message */
_puts_err(": command not found\n");
}
/**

exec_cmd - executes the command

@info: pointer to struct containing information about the shell

Return: returns nothing
*/
void exec_cmd(info_t *info)
{
pid_t child_pid = 0;
int status = 0;

child_pid = fork(); /* create a child process /
if (child_pid == -1) / if forking fails /
{
perror("fork"); / print error message /
exit(EXIT_FAILURE); / exit with failure /
}
if (child_pid == 0) / if in child process /
{
if (execve(info->fullpath, info->argv, environ) == -1) / execute the command /
{
perror("execve"); / print error message /
exit(EXIT_FAILURE); / exit with failure /
}
}
else / if in parent process /
{
waitpid(child_pid, &status, WUNTRACED); / wait for child process to complete /
if (WIFEXITED(status)) / if child process exits normally /
info->status = WEXITSTATUS(status); / set exit status in info struct */
}
}

/**

sig_handler - handles signal interruption
@sig: signal number
Return: returns nothing
/
void sig_handler(int sig)
{
(void) sig;
write(STDOUT_FILENO, "\n$ ", 3); / print prompt after interrupt */
}
/**

main - main function of the shell program

@argc: number of command line arguments

@argv: array of strings containing command line arguments

Return: returns the exit status of the shell
*/
int main(int argc, char **argv)
{
info_t *info = NULL;

signal(SIGINT, sig_handler); /* handle SIGINT signal /
info = init_info(); / initialize info struct /
if (!info) / if initialization fails /
return (EXIT_FAILURE); / exit with failure /
if (argc == 1) / if no command line arguments /
return (hsh(info, argv)); / run shell in interactive mode /
else / if command line arguments /
{
if (!read_script(info, argv[1])) / read from script file /
return (EXIT_FAILURE); / exit with failure /
return (info->status); / return exit status of the script */
}
}










