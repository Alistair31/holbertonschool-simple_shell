#include "man.h"
/**
 * _builtin - checks and executes built-in commands
 * @args: array of command arguments
 * @_env: environment variables
 *
 * Return: 1 if a built-in command was executed, 0 otherwise
 */
int _builtin(char **args, char **_env)
{
	if (!args || !args[0])
		return (0);

	if (strcmp(args[0], "env") == 0)
		return (builtin_env(_env));

	if (strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	return (0);
}
/**
 * builtin_exit - built-in command to exit the shell
 * @args: array of command arguments
 *
 * Return: -1 to indicate shell should exit
 */
int builtin_exit(char **args)
{
	(void)args;
	return (-1);
}
/**
 * builtin_env - built-in command to print environment variables
 * @_env: environment variables
 *
 * Return: 1 on success, 0 if @_env is NULL
 */
int builtin_env(char **_env)
{
	int i = 0;

	if (!_env)
		return (0);

	while (_env[i])
	{
		printf("%s\n", _env[i]);
		i++;
	}
	return (1);
}
