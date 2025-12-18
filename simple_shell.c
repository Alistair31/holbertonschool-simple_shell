#include "man.h"

/**
 * command - executes a command
 * @args: array of arguments
 *
 * Return: void
 */
void command(char **args)
{
	pid_t pid;
	int status, i, j = 0;

	for (i = 0; args[i] ; i++)
			if (strcmp(args[i], "exit") == 0)
			{
				while (args[j])
				{
					free(args[j]);
					j++;
				}
				free(args);
				fprintf(stderr, "%s\n", "Error");
				exit(2);
			}


	pid = fork();

	if (pid == -1)
	{
		perror("Error: ");
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		return;
	}

	if (pid == 0)
	{
		execve(args[0], args, NULL);
		perror("Error");
		exit(1);
	}
	else
	{
		wait(&status);
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args);
	}
}
/**
 * main - entry point for the simple shell
 *
 * Return: 0 on success
 */
int main(void)
{
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		char **wordstr = bunchwords(interactive);

		if (wordstr == NULL)
		{
			printf("\n");
			break;
		}

		if (wordstr[0] == NULL)
		{
			free(wordstr);
			continue;
		}

		command(wordstr);
	}
	return (0);
}
