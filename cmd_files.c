#include "shell.h"

int cant_open(char *file_path);

/**
 * cant_open - print cant error
 * @file_path: Path to file
 * Return: 127
*/

int cant_open(char *file_path)
{
	char *err, *his_str;
	int length;

	his_str = _itoa(his);
	if (!his_str)
		return (127);

	length = _strlen(name) + _strlen(his_str) + _strlen(file_path) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(his_str);
		return (127);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, his_str);
	_strcat(err, ": Can't open ");
	_strcat(err, file_path);
	_strcat(err, "\n");

	free(his_str);
	write(STDERR_FILENO, err, length);
	free(err);
	return (127);
}

int  cmd_file(char *file_path, int *_exe);

/**
 * cmd_file - Run commands in file
 * @file_path: Path to file
 * @_exe: Return value of last executed command
 * Return: 127,  -1 or return value of last command
*/
int  cmd_file(char *file_path, int *_exe)
{
	ssize_t file, b_rd, x;
	unsigned int line_size = 0;
	unsigned int prev_size = 120;
	char *line, **args, **frt;
	char buff[120];
	int ret;

	his = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*_exe = cant_open(file_path);
		return (*_exe);
	}
	line = malloc(sizeof(char) * prev_size);
	if (!line)
		return (-1);
	do {
		b_rd = read(file, buff, 119);
		if (b_rd == 0 && line_size == 0)
			return (*_exe);
		buff[b_rd] = '\0';
		line_size += b_rd;
		line = _realloc(line, prev_size, line_size);
		_strcat(line, buff);
		prev_size = line_size;
	} while (b_rd);
	for (x = 0; line[x] == '\n'; x++)
		line[x] = ' ';
	for (; x < line_size; x++)
	{
		if (line[x] == '\n')
		{
			line[x] = ';';
			for (x += 1; x < line_size && line[x] == '\n'; x++)
				line[x] = ' ';
		}
	}
	replace_vars(&line, _exe);
	format_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*_exe = 2;
		free_args(args, args);
		return (*_exe);
	}
	frt = args;

	for (x = 0; args[x]; x++)
	{
		if (_strncmp(args[x], ";", 1) == 0)
		{
			free(args[x]);
			args[x] = NULL;
			ret = call_args(args, frt, _exe);
			args = &args[++x];
			x = 0;
		}
	}

	ret = call_args(args, frt, _exe);

	free(frt);
	return (ret);
}
