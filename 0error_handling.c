#include "shell.h"

/**
  *num_len - finds digit length of number
  *@num: integer value
  *Return: digit's length
  */

int num_len(int num)
{
	unsigned int x;
	int len = 1;

	if (num < 0)
	{
		len++;
		x = num * -1;
	}
	else
	{
		x = num;
	}

	while (x > 9)
	{
		len++;
		x /= 10;
	}
	return (len);
}

/**
  *_itoa - converts int to string
  *@num: integer value
  *Return: string
  */

char *_itoa(int num)
{
	char *buff;
	int len = num_len(num);
	unsigned int x;

	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	buff[len] = '\0';

	if (num < 0)
	{
		x = num * -1;
		buff[0] = '-';

		else
		{
			x = num;
		}

		len--;
		do {
			buff[len] = (x % 10) + '0';
			x /= 10;
			len--;
		}
		while (x > 0)
			return (buff);
	}
}

/**
  *create_err - custom error msg to stderr
  *@args: an array of arguments
  *@err: the error val
  *Return: err value
  */
int create_err(char **args, int err)
{
	char *error;

	switch (err)
	{
		case -1:
		error = err_env(args);
		break;
		case 1:
		error = err0(args);
		break;
		case 2:
		if (*(args[0]) == 'e')
			error = err1_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = err3_syntax(args);
		else
			error = err2_cd(args);
		break;
		case 126:
		error = err026(args);
		break;
		case 127:
		error = err027(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));
	if (error)
		free(error);
	return (err);
}
