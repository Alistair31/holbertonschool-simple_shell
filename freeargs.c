#include "man.h"
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
