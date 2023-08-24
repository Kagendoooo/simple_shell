#include "shell.h"

/**
 * err_env - error message for shellby_env errors.
 * @args: arguments passed to the command
 * Return: error string
 */
char *err_env(char **args)
{
	char *error, *his_str;
	int len;


	his_str = _itoa(his);
	if (!his_str)
		return (NULL);


	args--;
	len = _strlen(name) + _strlen(his_str) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(his_str);
		return (NULL);
	}


	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, his_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from envrment\n");


	free(his_str);
	return (error);
}


/**
 * err0 - an error message for shellby_alias errors
 * @args: arguments passed to the command
 * Return: error string
 */
char *err0(char **args)
{
	char *error;
	int len;


	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);


	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");


	return (error);
}


/**
 * err1_exit - error message for _exit errors
 * @args: arguments passed to the command
 * Return: error string
 */
char *err1_exit(char **args)
{
	char *error, *his_str;
	int len;


	his_str = _itoa(his);
	if (!his_str)
		return (NULL);


	len = _strlen(name) + _strlen(his_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(his_str);
		return (NULL);
	}


	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, his_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");


	free(his_str);
	return (error);
}


/**
 * err2_cd - error message for shellby_cd errors
 * @args: arguments passed to the command
 * Return: error string
 */
char *err2_cd(char **args)
{
	char *error, *his_str;
	int len;


	his_str = _itoa(his);
	if (!his_str)
		return (NULL);


	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(his_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(his_str);
		return (NULL);
	}


	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, his_str);
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");


	free(his_str);
	return (error);
}


/**
 * err3_syntax - error message for syntax errors
 * @args: arguments passed to the command
 * Return: error string.
 */
char *err3_syntax(char **args)
{
	char *error, *his_str;
	int len;


	his_str = _itoa(his);
	if (!his_str)
		return (NULL);


	len = _strlen(name) + _strlen(his_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(his_str);
		return (NULL);
	}


	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, his_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");


	free(his_str);
	return (error);
}

