#include "shell.h"

/**
 * man_env - displays information on the shellby builtin command env
 */
void man_env(void)
{
	char *msg = "env: env\n\tPrints the current envrment.\n";


	write(STDOUT_FILENO, msg, _strlen(msg));
}


/**
 * man_setenv - displays information on the shellby builtin command setenv
 */
void man_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";


	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "envrment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}


/**
 * man_unsetenv - displays information on the builtin command unsetenv
 */
void man_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";


	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "envrmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
