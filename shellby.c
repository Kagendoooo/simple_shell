#include "shell.h"

/**
 *_builtin - links a command with corresponding shellby bultin fn
 *@command: command
 *Return: pointer to corresponding bultin
 */

int (*_builtin(char *command))(char **args, char **frt)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{NULL, NULL}
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 *shellby_exit - process termination
 *@args: array of arguments
 *Return: 2 or 0
 */
int shellby_exit(char **args, char **frt)
{
	int i = 0, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[1])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_err(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_err(--args, 2));
	args -= 1;
	free_args(args, frt);
	free_env();
	free_alias_list(aliases);
	exit(num);
}


/**
 *shellby_cd - changes current directory
 *@args: array of arguments
 *@frt: double pointer to args
 *Return: -2, -1 or 0
 */

int shellby_cd(char **args, char __attribute__((__unused__)) **frt)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);
	if (args[0])
	{
		if (args[0])
		{
			if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
			{
				if ((args[0][1] == '-' && args[0][2] == '\0') ||
						args[0][1] == '\0')
				{
					if (_getenv("OLDPWD") != NULL)
						(chdir(*_getenv("OLDPWD") + 7));
				}
				else
				{
					free(oldpwd);
					return (create_err(args, 2));
				}
			}
			else
			{
				if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
						&& ((dir.st_mode & S_IXUSR) != 0))
					chdir(args[0]);
				else
				{
					free(oldpwd);
					return (create_err(args, 2));
				}
			}
		}
		else
		{
			if (_getenv("HOME") != NULL)
				chdir(*(_getenv("HOME")) + 5);
		}
	}
		pwd = getcwd(pwd, 0);
		if (!pwd)
			return (-1);
		dir_info = malloc(sizeof(char *) * 2);
		if (!dir_info)
			return (-1);
		dir_info[0] = "OLDPWD";
		dir_info[1] = oldpwd;
		if (_setenv(dir_info, dir_info) == -1)
			return (-1);
		dir_info[0] = "PWD";
		dir_info[1] = pwd;
		if (_setenv(dir_info, dir_info) == -1)
			return (-1);
		if (args[0] && args[0][0] == '-' && args[0][1] != '-')
		{
			write(STDOUT_FILENO, pwd, _strlen(pwd));
			write(STDOUT_FILENO, new_line, 1);
		}
		free(oldpwd);
		free(pwd);
		free(dir_info);
		return (0);
}

/**
 * shellby_help - shows information about shellby builtin commands
 * @args:  array of arguments
 * @frt:  pointer to the beginning of args
 * Return: 0/ -1
 */

int shellby_help(char **args, char __attribute__((__unused__)) **frt)
{
	if (!args[0])
		man_all();
	else if (_strcmp(args[0], "alias") == 0)
		man_alias();
	else if (_strcmp(args[0], "cd") == 0)
		man_cd();
	else if (_strcmp(args[0], "exit") == 0)
		man_exit();
	else if (_strcmp(args[0], "env") == 0)
		man_env();
	else if (_strcmp(args[0], "setenv") == 0)
		man_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		man_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		man_help();
	else
		write(STDERR_FILENO, name, _strlen(name));


	return (0);
}

