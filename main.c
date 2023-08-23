#include "shell.h"

void sig_handler(int sig);

/**
 * sig_handler - Print a new prompt upon a signal
 * @sig: The signal
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * main - Runs a simple UNIX command interpreter
 * @argc: The number of arguments supplied to the program
 * @argv: An array of pointers to the arguments
 * Return: The return value of the last executed command
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *_exe = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	his = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*_exe = 0;
	envr = _copyenv();
	if (!envr)
		exit(-100);

	if (argc != 1)
	{
		ret =  cmd_file(argv[1], _exe);
		free_env();
		free_alias_list(aliases);
		return (*_exe);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = format_args(_exe);
		free_env();
		free_alias_list(aliases);
		return (*_exe);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = format_args(_exe);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*_exe);
		}
	}
}
