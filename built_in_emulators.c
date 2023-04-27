#include "main.h"

/**
 * _myexit - Clean up and terminate program execution.
 * @info: Pointer to the info_t structure.
 *
 * Description: This function is responsible for cleaning up any resources
 * allocated by the program and terminating its execution. It takes a pointer
 * to the info_t structure, which contains information about the program state
 * and resources.
 *
 * Return: Integer value indicating the exit status of the program.
 */

int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Custom implementation of the cd command.
 * @info: Pointer to a struct containing relevant information.
 *
 * This function is responsible for changing the current working directory.
 * It receives a pointer to a struct `info` which contains necessary details.
 *
 * Return: 0 on success, -1 on failure.
 */

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Provides help information based on the given `info` struct.
 *
 * @info: Pointer to the `info_t` struct containing relevant information.
 *
 * Return: An integer indicating the status of the help operation.
 */

int _myhelp(info_t *info)
{
char **arg_array;
int i;
arg_array = info->argv;
_puts("help call works. Function not yet implemented\n");
for (i = 0; i < 1; i++)
{
	_puts(*arg_array); /* temp att_unused workaround */
}
return (0);
}
