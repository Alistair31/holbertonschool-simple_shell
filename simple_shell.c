#include "man.h"

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

char **bunchwords(void)
{
	size_t line = 0;
	char *str = NULL;
	ssize_t nread;
	char **args;

	printf("$ ");
	nread = getline(&str, &line, stdin);

	if (nread == -1)
	{
		free(str);
		return (NULL);
	}

	if (str[nread - 1] == '\n')
		str[nread - 1] = '\0';

	args = split_words(str);
	free(str);
	return (args);
}

int main(void)
{
	int status, i;

	while (1)
	{
		pid_t pid;
		char **wordstr = bunchwords();

		if (wordstr == NULL)
			break;

		pid = fork();

		if (pid == -1)
		{
			perror("Error: ");
			for (i = 0; wordstr[i]; i++)
				free(wordstr[i]);
			free(wordstr);
			continue;
		}

		if (pid == 0)
		{
			execve(wordstr[0], wordstr, NULL);
			perror("Error");
			exit(1);
		}
		else
		{
			wait(&status);
			for (i = 0; wordstr[i]; i++)
				free(wordstr[i]);
			free(wordstr);
		}
	}
	return (0);
}
