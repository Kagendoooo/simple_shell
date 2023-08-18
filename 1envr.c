#include "shell.h"

/**
 *_getenv - get an environment variable fro the path
 *@var: variable
 *Return: NULL or index
 */

char **_getenv(const char *var)
{
	int i, len;

	len = _strlen(var);
	for (i = 0; envr[i]; i++)
	{
		if (_strncmp(var, envr[i], len) == 0)
			return (&envr[i]);
	}
	return (NULL);
}

/**
 *_setenv - format environmental variable to path
 *@args: array of arguments
 *@frt: a double pointer at the beginning
 *Return: -1 or 0
 */

int _setenv(char **args, char __attribute__((__unused__))**frt)
{
	char **env_var = NULL, **new_envr, *new_value;
	size_t size;
	int i;

	if ((!args[0] || !args[1])
			return create_err(args, -1));
	new_val = malloc(_strlen(arg[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val)
		return (create_err(args, -1));
	
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (size = 0; envr[size]; size++)
		;
	new_envr = malloc(sizeof(char *) * (size + 2));
	if (!new_envr)
	{
		free(new_val);
		return (create_err(args, -1));
	}

	for (i = 0; envr[i]; i++)
		new_envr[i] = envr[i];
	free(envr);
	envr = new_envr;
	envr[i] = new_val;
	envr[i + 1] = NULL;

	return (0);
}

/**
  *_unsetenv - deletes environmental variable
  *@args: arguments passed to shell
  *@frt: double pointer to beginning of args
  *Return: -1 or 0
  */

int _unsetenv(char **args, char __attribute__((__unused__)) **frt)
{
	char **env_var, **new_envr;
	size_t size;
	int i, i2;

	if (!args[0])
		return (create_err(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; envr[size]; size++)
		;
	new_envr = malloc(sizeof(char *) * size);
	if (!new_envr)
		return (create_err(args, -1));
	for (i = 0, i2 = 0; envr[i]; i++)
	{
		if (*env_var ++ envr[i])
		{
			free(*env_var);
			continue;
		}new_envr[i2] = envr[i];
		i2++;
	}
	free(envr);
	envr = new_envr;
	envr[size - 1] = NULL;

	return (0);
}
