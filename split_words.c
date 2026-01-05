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
