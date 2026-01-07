#include "man.h"
/**
 * split_words - splits a string into words
 * @str: input string
 *
 * Return: array of strings (words)
 */
char **split_words(char *str)
{
	char **arstr;
	char *token;
	int i = 0;

	if (!str)
		return (NULL);

	arstr = malloc(sizeof(char *) * (strlen(str) + 1));
	if (!arstr)
		return (NULL);

	token = strtok(str, " \t\n");
	while (token)
	{
		arstr[i] = _strdup(token);
		if (!arstr[i])
		{
			while (i > 0)
			{
				free(arstr[--i]);
			}
			free(arstr);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t\n");
	}
	arstr[i] = NULL;
	return (arstr);
}

/**
 * split_line - reads a line and splits it into words
 * @interactive: flag for interactive mode
 *
 * Return: array of strings (words)
 */
char **split_line(int interactive)
{
	size_t line = 0;
	char *str = NULL;
	ssize_t nread;
	char **args;

	while (1)
	{
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
			continue;
		}
		args = split_words(str);
		free(str);
		return (args);
	}

	return (NULL);
}
