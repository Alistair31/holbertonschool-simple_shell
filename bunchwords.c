#include "man.h"
/**
 * bunchwords - reads a line and splits it into words
 * @interactive: flag for interactive mode
 *
 * Return: array of strings (words)
 */
char **bunchwords(int interactive)
{
	size_t line = 0;
	char *str = NULL;
	ssize_t nread;
	char **args;

	if (interactive)
	{
		printf("$ ");
		fflush(stdout);
	}

	nread = getline(&str, &line, stdin);
	if (nread == -1)
	{
		free(str);
		return (NULL);
	}

	if (nread > 0 && str[nread - 1] == '\n')
		str[nread - 1] = '\0';

	if (*str == '\0')
	{
		free(str);
		return (NULL);
	}

	args = split_words(str);
	free(str);
	return (args);
}
