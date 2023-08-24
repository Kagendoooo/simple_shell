#include "shell.h"

/**
  *err026 - creates an error message for denied permission failure
  *@args: an array of arguments
  *Return: error string
  */

char *err026(char **args)
{
	char *error, *his_str;
	int len;

	his_str = _itoa(his);
	if (!his_str)
		return (NULL);

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
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");
	free(his_str);
	return (error);
}

/**
  *err027 - error message for commands not found
  *@args: arguments passed
  *Return: error string
  */

char *err027(char **args)
{
	char *error, *his_str;
	int len;

	his_str = _itoa(his);
	if (!his_str)
		return (NULL);
	len = _strlen(name) + _strlen(his_str) + _strlen(args[0]) + 16;
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
	_strcat(error, ": not found\n");
	free(his_str);
	return (error);
}
