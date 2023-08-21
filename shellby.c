#include "shell.h"

/**
 *_builtin - links a command with corresponding shellby bultin fn
 *@command: command
 *Return: pointer to corresponding bultin
 */

int (*_builtin(char *command))(char **args, char **frt)
{
	builtin_t funcs[] = {
		{ "exit", _exit },
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
  *_exit - process termination
  *@args: array of arguments
  *Return: 2 or 0
  */
int _exit(char **args)
{
	int i = 0, len_of_int = 10;
	unsigned int num = 0;

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

