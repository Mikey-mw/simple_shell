#include "shell.h"

/**
 * _terminateShell - exits the shell
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if data->argv[0] != "exit"
 */
int _terminateShell(info_t *data)
{
	int exitCheck;

	if (data->argv[1])  /* If there is an exit argument */
	{
		exitCheck = _errAtoi(data->argv[1]);
		if (exitCheck == -1)
		{
			data->status = 2;
			printError(data, "Illegal number: ");
			_ePuts(data->argv[1]);
			_ePutchar('\n');
			return (1);
		}
		data->errNum = _errAtoi(data->argv[1]);
		return (-2);
	}
	data->errNum = -1;
	return (-2);
}

/**
 * _changeDirectory - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _changeDirectory(info_t *data)
{
	char *str, *directory, buffer[1024];
	int chdirRet;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		directory = _getEnv(data, "HOME=");
		if (!directory)
			chdirRet = /* TODO: what should this be? */
				chdir((directory = _getEnv(data, "PWD=")) ? directory : "/");
		else
			chdirRet = chdir(directory);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getEnv(data, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getEnv(data, "OLDPWD=")), _putchar('\n');
		chdirRet = /* TODO: what should this be? */
			chdir((directory = _getEnv(data, "OLDPWD=")) ? directory : "/");
	}
	else
		chdirRet = chdir(data->argv[1]);
	if (chdirRet == -1)
	{
		printError(data, "can't cd to ");
		_ePuts(data->argv[1]), _ePutchar('\n');
	}
	else
	{
		_setEnv(data, "OLDPWD", _getEnv(data, "PWD="));
		_setEnv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _showHelp - displays help information
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _showHelp(info_t *data)
{
	char **argArray;

	argArray = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray); /* temp att_unused workaround */
	return (0);
}

