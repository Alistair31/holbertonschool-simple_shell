#include "man.h"

/**
 * findcmd - finds and executes a command
 * @args: array of command arguments
 * @_env: environment variables
 * @last_status: last command exit status
 *
 * This function first checks if the command is a direct executable path.
 * If not, it searches for the command in the PATH environment variable.
 *
 * Return: exit status of the command execution, or 127 if not found
 */
int findcmd(char **args, char **_env, int last_status)
{
	int status;

	if (!args || !args[0])
		return (last_status);

	status = handle_path(args, _env);
	if (status != -1)
		return (status);
	status = search_path(args, _env);
	if (status != -1)
		return (status);

	fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
	return (127);
}

/**
 * get_path - retrieves the PATH variable from the environment
 * @_env: environment variables
 *
 * Return: pointer to PATH string, or NULL if not found
 */
char *get_path(char **_env)
{
	int i = 0;

	if (!_env)
		return (NULL);

	while (_env[i])
	{
		if (strncmp(_env[i], "PATH=", 5) == 0)
			return (_env[i] + 5);
		i++;
	}
	return (NULL);
}
