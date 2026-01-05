#include "man.h"
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
