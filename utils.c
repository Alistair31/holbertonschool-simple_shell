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

/**
 * free_args - frees a NULL-terminated array of strings
 * @args: array of strings to free
 */
void free_args(char **args)
{
	size_t i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * _strdup - duplicates a string
 * @s: input string
 *
 * Return: pointer to duplicated string, or NULL on failure
 */
char *_strdup(const char *s)
{
	char *dup;
	size_t len;

	if (!s)
		return (NULL);

	len = strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	strcpy(dup, s);
	return (dup);
}
