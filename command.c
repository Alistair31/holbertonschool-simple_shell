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
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, _env);
		perror(args[0]);
		exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
}
