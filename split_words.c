#include "man.h"
/**
 * split_words - splits a string into words
 * @str: input string
 *
 * Return: array of strings (words)
 */
char **split_words(char *str)
{
	char **arstr = NULL;
	char *tmp = NULL;
	int i, j = 0, words = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == ' ')
			words++;
	}

	arstr = malloc(sizeof(char *) * (words + 2));
	if (!arstr)
		return (NULL);

	tmp = strtok(str, " ");
	while (tmp)
	{
		arstr[j++] = strdup(tmp);
		tmp = strtok(NULL, " ");
	}
	arstr[j] = NULL;

	return (arstr);
}
