#include "shell.h"

/**
  *_copyenv - creates a copy of environment
  *Return: NULL/0
  */
char **_copyenv(void)
{
	char **new_envr;
	size_t s;
	int i;

	for (s = 0; environ[s]; s++)
		;
	new_envr = malloc(sizeof(char *) * (s + 1));
	if (!new_envr)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		new_envr[i] = malloc(_strlen(environ[i]) + 1);
		if (!new_envr[i])
		{
			for (i--; i >= 0; i--)
				free(new_envr[i]);
			free(new_envr);
			return (NULL);
		}
		_strcpy(new_envr[i], environ[i]);
	}
	new_envr[i] = NULL;
	return (new_envr);
}

/**
  *free_env -frees environment copy
  */
void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
  *_getenv - gets an environment var from PATH
  *@var: name of envr variable
  *Return: NULL / pointer to var
  */

char **_getenv(const char *var)
{
	int i, len;

	len = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], len) == 0)
			return (&environ[i]);
	}
	return (NULL);
}
