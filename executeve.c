#include "man.h"

char **bunchwords(void)
{
	size_t line = 0;
	char *str = NULL;
	char **arstr = NULL;
	char *tmp = NULL;
	ssize_t nread;
	int i, j = 0;

	while (1)
	{
		i = 0;
		printf("$ ");
		nread = getline(&str, &line, stdin);

		if (nread == -1)
		{
			free(str);
			return (NULL);
		}

		if (str[nread - 1] == '\n')
			str[nread - 1] = '\0';

		for (; str[i]; i++)
		{
			if (str[i] == ' ')
				j++;
		}
		i = 0;
		tmp = strtok(str, " ");
		arstr = malloc(sizeof(char *) * j);
		if (!arstr)
			return (NULL);
		while (tmp != NULL)
		{
			arstr[i] = tmp;
			tmp = strtok(NULL, " ");
			i++;
		}
		arstr[i] = NULL;
		return (arstr);
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
