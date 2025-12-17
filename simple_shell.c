#include "man.h"

char **split_words(char *str)
{
	char **arstr = NULL;
	char *tmp = NULL;
	int i, words = 0;

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
		arstr[i++] = tmp;
		tmp = strtok(NULL, " ");
	}
	arstr[i] = NULL;

	return (arstr);
}

char **bunchwords(void)
{
	size_t line = 0;
	char *str = NULL;
	ssize_t nread;

	while (1)
	{
		printf("$ ");
		nread = getline(&str, &line, stdin);

		if (nread == -1)
		{
			free(str);
			return (NULL);
		}

		if (str[nread - 1] == '\n')
			str[nread - 1] = '\0';


		return (split_words(str));
	}
}

int main(void)
{
	int status;

	while (1)
	{
		pid_t pid;
		char **wordstr = bunchwords();

		pid = fork();
		if (wordstr == NULL)
			break;
		if (pid == -1)
		{
			perror("Error: ");
			return (1);
		}
		wait(&status);
		if (pid == 0)
		{
			execve(wordstr[0], wordstr, NULL);
			perror("Error");
		}
	}
	return (-1);
}
