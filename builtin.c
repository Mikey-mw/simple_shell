#include "shell.h"

/**
 * _exit_shell - exits the shell
 * @data: Structure containing potential arguments.
 * Return: exits with a given exit status
 *         (0) if data.argv[0] != "exit"
 */
int _exit_shell(info_t *data)
{
	int exit_check;

	if (data->argv[1])  /* If there is an exit argument */
	{
		exit_check = _err_atoi(data->argv[1]);
		if (exit_check == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}
		data->err_num = _err_atoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * _change_directory - changes the current directory of the process
 * @data: Structure containing potential arguments.
 * Return: Always 0
 */
int _change_directory(info_t *data)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		target_dir = _getenv(data, "HOME=");
		if (!target_dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((target_dir = _getenv(data, "PWD=")) ? target_dir : "/");
		else
			chdir_ret = chdir(target_dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((target_dir = _getenv(data, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		_eputs(data->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _show_help - displays help information
 * @data: Structure containing potential arguments.
 * Return: Always 0
 */
int _show_help(info_t *data)
{
	char **arg_array;

	arg_array = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
