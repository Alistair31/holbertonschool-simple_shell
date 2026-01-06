#include "man.h"

/**
 * main - entry point for the simple shell
 * @ac: argument count
 * @av: argument vector
 * @envp: environment variables
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **envp)
{
	int interactive = isatty(STDIN_FILENO);
	char **wordstr, **_env;
	int status;

	(void)ac;
	(void)av;

	_env = makeenv(envp);
	if (!_env)
		return (EXIT_FAILURE);

	while (1)
	{
		wordstr = split_line(interactive);
		if (!wordstr)
		{
			if (interactive)
				printf("\n");
			break;
		}

		status = _builtin(wordstr, _env);

		if (status == -1)
		{
			free_args(wordstr);
			break;
		}

		if (status == 1)
		{
			free_args(wordstr);
			continue;
		}

		findcmd(wordstr, _env);
		free_args(wordstr);
	}
	free_args(_env);
	return (0);
}
