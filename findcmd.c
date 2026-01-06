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
