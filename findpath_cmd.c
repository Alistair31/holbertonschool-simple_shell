#include "man.h"

/**
 * findcmd - finds and executes a command
 * @args: array of command arguments
 * @_env: environment variables
 *
 * This function first checks if the command is a direct executable path.
 * If not, it searches for the command in the PATH environment variable.
 */
void findcmd(char **args, char **_env)
{
	if (!args || !args[0])
		return;

	if (handle_path(args, _env))
		return;
	search_path(args, _env);
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
