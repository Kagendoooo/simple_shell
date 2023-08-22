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

	for (s = 0; envr[s]; s++)
		;
	new_envr = malloc(sieof(char *) * (s + 1));
	if (!new_envr)
		return (NULL);
	for (i = 0; envr[i]; i++)
	{
		new_envr[i] = malloc(_strlen(envr[i]) + 1);
		if (!new_envr[i])
		{
			for (i--; i >= 0; i--)
				free(new_envr[i]);
			free(new_envr);
			return (NULL);
		}
		_strcpy(new_envr[i], envr[i]);
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

	for (i = 0; envr[i]; i++)
		free(envr[i]);
	free(envr);
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
	for (i = 0; envr[i]; i++)
	{
		if (_strncmp(var, envr[i], len) == 0)
			return (&envr[i]);
	}
	return (NULL);
}
