#include "man.h"

/**
 * command - executes a command
 * @args: array of arguments
 * @_env: environment variables
 *
 * Return: void
 */
void command(char **args, char **_env)
{
	pid_t pid;

	if (!args || !args[0])
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		execve(args[0], args, _env);
		perror(args[0]);
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}
