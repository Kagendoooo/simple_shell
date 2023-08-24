#include "shell.h"

char *get_args(char *line, int *_exe);

/**
 * get_args - Get command from std input
 * @line: buffer to store command
 * @_exe: return value of last executed command
 * Return: Pointer or NULL
*/
char *get_args(char *line, int *_exe)
{
	size_t x = 0;
	ssize_t rd;
	char *pr = "$ ";

	if (line)
		free(line);

	rd = _getline(&line, &x, STDIN_FILENO);
	if (rd == -1)
		return (NULL);
	if (rd == 1)
	{
		his++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, pr, 2);
		return (get_args(line, _exe));
	}

	line[rd - 1] = '\0';
	replace_vars(&line, _exe);
	format_line(&line, rd);

	return (line);
}

int call_args(char **args, char **frt, int *_exe);

/**
 * call_args - Partitions operators from commands
 * call commands
 * @args: arguments
 * @frt: double pointer
 * @_exe: return value of the parent process' last executed command
 * Return: The return value of the last executed command
*/
int call_args(char **args, char **frt, int *_exe)
{
	int ret, idx;

	if (!args[0])
		return (*_exe);
	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], "||", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = rpc_aliases(args);
			ret = exe_args(args, frt, _exe);
			if (*_exe != 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ret);
			}
		}
		else if (_strncmp(args[idx], "&&", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = rpc_aliases(args);
			ret = exe_args(args, frt, _exe);
			if (*_exe == 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ret);
			}
		}
	}
	args = rpc_aliases(args);
	ret = exe_args(args, frt, _exe);
	return (ret);
}

int exe_args(char **args, char **frt, int *_exe);

/**
 * exe_args - Call execution of command
 * @args: arguments.
 * @frt: double pointer
 * @_exe: return value of the parent process' last executed command
 * Return: The return value of the last executed command
*/
int exe_args(char **args, char **frt, int *_exe)
{
	int ret, x;
	int (*builtin)(char **args, char **frt);

	builtin = _builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, frt);
		if (ret != EXIT)
			*_exe = ret;
	}
	else
	{
		*_exe = execute(args, frt);
		ret = *_exe;
	}

	his++;

	for (x = 0; args[x]; x++)
		free(args[x]);

	return (ret);
}

int format_args(int *_exe);

/**
 * format_args - Gets, calls, and runs the execution of a command
 * @_exe: return value of the parent process' last executed command
 * Return:  END_OF_FILE (-2) or -1 or value off last executed command
*/
int format_args(int *_exe)
{
	int ret = 0, idx;
	char **args, *line = NULL, **frt;

	line = get_args(line, _exe);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*_exe = 2;
		free_args(args, args);
		return (*_exe);
	}
	frt = args;

	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], ";", 1) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			ret = call_args(args, frt, _exe);
			args = &args[++idx];
			idx = 0;
		}
	}
	if (args)
		ret = call_args(args, frt, _exe);

	free(frt);
	return (ret);
}

int check_args(char **args);

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments
 * Return: -2 orr 0
*/
int check_args(char **args)
{
	size_t x;
	char *current, *next;

	for (x = 0; args[x]; x++)
	{
		current = args[x];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (x == 0 || current[1] == ';')
				return (create_err(&args[x], 2));
			next = args[x + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (create_err(&args[x + 1], 2));
		}
	}
	return (0);
}
