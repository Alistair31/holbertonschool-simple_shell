#include "man.h"
/**
 * makeenv - creates a copy of the environment variables
 * @envp: original environment variables
 *
 * Return: newly allocated array of environment variable strings
 */
char **makeenv(char **envp)
{
	int i, size = 0;
	char **newenv;

	if (!envp)
		return (NULL);

	while (envp[size])
		size++;

	newenv = malloc(sizeof(char *) * (size + 1));
	if (!newenv)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		newenv[i] = _strdup(envp[i]);
		if (!newenv[i])
		{
			free_args(newenv);
			return (NULL);
		}
	}
	newenv[size] = NULL;
	return (newenv);
}
