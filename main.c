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

int execute(char **args, char **frt);

/**
 * execute - Executes command in child process
 * @args: arguments
 * @frt: A double pointer
 * Return: Value of last command or error code
*/
int execute(char **args, char **frt)
{
	pid_t child_pid;
	int sts, fg = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		fg = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_err(args, 126));
		else
			ret = (create_err(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (fg)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, envr);
			if (errno == EACCES)
				ret = (create_err(args, 126));
			free_env();
			free_args(args, frt);
			free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&sts);
			ret = WEXITSTATUS(sts);
		}
	}
	if (fg)
		free(command);
	return (ret);
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
