#include "man.h"

/**
 * free_args - free the list of arguments
 * @args: argument to free
 */
void free_args(char **args)
{
	int k;

	for (k = 0; args[k]; k++)
		free(args[k]);
	free(args);
}
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
	char *spath;

	for (i = 0; args[i]; i++)
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
	spath = shellpath(args[0]);
	if (spath == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		free_args(args);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error: ");
		free_args(args);
		exit(127);
	}
	if (pid == 0)
	{
		execve(spath, args, NULL);
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		free(spath);
		exit(127);
	}
	else
	{
		wait(&status);
		free(spath);
		free_args(args);
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
		int i = 0;

		if (wordstr == NULL)
		{
			if (interactive)
				printf("\n");
			break;
		}

		if (wordstr[0] == NULL)
		{
			free(wordstr);
			continue;
		}
		if (strcmp(wordstr[0], "exit") == 0)
		{
			while (wordstr[i])
			{
				free(wordstr[i]);
				i++;
			}
			free(wordstr);
			break;
		}

		command(wordstr);
	}
	return (0);
}
