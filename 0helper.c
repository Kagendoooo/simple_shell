#include "shell.h"

void free_args(char **args, char **frt);

/**
 * free_args - Frees up memory
 * @args: A pointer containing arguments
 * @frt: A double pointer to args
*/
void free_args(char **args, char **frt)
{
	size_t x;

	for (x = 0; args[x] || args[x + 1]; x++)
		free(args[x]);

	free(frt);
}

char *get_pid(void);

/**
 * get_pid - Gets the current PID
 * Opens the stat file
 * Return:PID or NULL
 */
char *get_pid(void)
{
	size_t x = 0;
	char *buff;
	ssize_t fl;

	fl = open("/proc/self/stat", O_RDONLY);
	if (fl == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(fl);
		return (NULL);
	}
	read(fl, buff, 120);
	while (buff[x] != ' ')
		x++;
	buff[x] = '\0';

	close(fl);
	return (buff);
}

char *get_env_value(char *beginning, int len);

/**
 * get_env_value - Gets value corresponding to envrtl var
 * @beginning: envrtl var
 * @len: length of the envrtl var
 * Return: value of envrtl var
*/
char *get_env_value(char *beginning, int len)
{
	char **var_address;
	char *rep = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_address = _getenv(var);
	free(var);
	if (var_address)
	{
		temp = *var_address;
		while (*temp != '=')
			temp++;
		temp++;
		rep = malloc(_strlen(temp) + 1);
		if (rep)
			_strcpy(rep, temp);
	}

	return (rep);
}

void replace_vars(char **line, int *_exe);

/**
 * replace_vars - Deals with var replacement
 * @line: A double pointer
 * @_exe: A pointer to return value of last command executed
*/
void replace_vars(char **line, int *_exe)
{
	int y, z = 0, len;
	char *rplcmnt = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (y = 0; old_line[y]; y++)
	{
		if (old_line[y] == '$' && old_line[y + 1] &&
				old_line[y + 1] != ' ')
		{
			if (old_line[y + 1] == '$')
			{
				rplcmnt = get_pid();
				z = y + 2;
			}
			else if (old_line[y + 1] == '?')
			{
				rplcmnt = _itoa(*_exe);
				z = y + 2;
			}
			else if (old_line[y + 1])
			{
				/* extract the variable name to search for */
				for (z = y + 1; old_line[z] &&
						old_line[z] != '$' &&
						old_line[z] != ' '; z++)
					;
				len = z - (y + 1);
				rplcmnt = get_env_value(&old_line[y + 1], len);
			}
			new_line = malloc(y + _strlen(rplcmnt)
					+ _strlen(&old_line[z]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, y);
			if (rplcmnt)
			{
				_strcat(new_line, rplcmnt);
				free(rplcmnt);
				rplcmnt = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			y = -1;
		}
	}
}
