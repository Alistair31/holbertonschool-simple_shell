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
	int status, last_status;
	(void)ac;
	(void)av;

	last_status = 0;
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
		last_status = findcmd(wordstr, _env);
		free_args(wordstr);
	}
	free_args(_env);
	if (last_status == 1)
		last_status = 127;
	/*printf("%d", last_status);*/ /*verify the exit status*/
	exit(last_status);
	return (0);
}
