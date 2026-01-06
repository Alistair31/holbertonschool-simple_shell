#include "man.h"

/**
 * build_fullpath - constructs a full path from dir + command
 * @dir: directory string
 * @cmd: command string
 *
 * Return: malloc'ed string containing full path, or NULL on failure
 */
char *build_fullpath(const char *dir, const char *cmd)
{
	size_t len;
	char *fullpath;

	if (!dir || !cmd)
		return (NULL);

	len = strlen(dir) + strlen(cmd) + 2;
	fullpath = malloc(len);
	if (!fullpath)
		return (NULL);

	sprintf(fullpath, "%s/%s", dir, cmd);
	return (fullpath);
}

/**
 * find_executable_in_path - searches PATH for an executable command
 * @cmd: command string
 * @_env: environment variables
 *
 * Return: malloc'ed full path if found, NULL otherwise
 */
char *find_executable_in_path(const char *cmd, char **_env)
{
	char *path_dup, *_path, *dir, *fullpath;

	if (!cmd || !cmd[0])
		return (NULL);

	_path = get_path(_env);
	if (!_path)
		return (NULL);
	path_dup = _strdup(_path);
	if (!path_dup)
	{
		perror("strdup");
		return (NULL);
	}

	dir = strtok(path_dup, ":");
	while (dir)
	{
		fullpath = build_fullpath(dir, cmd);
		if (!fullpath)
		{
			perror("malloc");
			break;
		}

		if (access(fullpath, X_OK) == 0)
		{
			free(path_dup);
			return (fullpath);
		}

		free(fullpath);
		dir = strtok(NULL, ":");
	}

	free(path_dup);
	return (NULL);
}

/**
 * search_path - searches for a command in PATH and executes it
 * @args: array of command arguments
 * @_env: environment variables
 */
void search_path(char **args, char **_env)
{
	char *fullpath, *old;

	if (!args || !args[0])
		return;

	fullpath = find_executable_in_path(args[0], _env);
	if (fullpath)
	{
		old = args[0];
		args[0] = fullpath;
		command(args, _env);
		args[0] = old;
		free(fullpath);
	}
	else
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
	}
}
/**
 * is_direct_executable - checks if a path is a direct executable
 * @path: path string
 *
 * Return: malloc'ed path if executable, NULL otherwise
 */
char *is_direct_executable(const char *path)
{
	if (!path || !path[0])
		return (NULL);

	if (path[0] == '/')
	{
		if (access(path, X_OK) == 0)
			return (_strdup(path));
		perror(path);
	}
	if (path[0] == '.')
	{
		if (path[1] == '/')
		{
			if (access(path, X_OK) == 0)
				return (_strdup(path));
			perror(path);
		}
		else if (path[1] == '.' && path[2] == '/')
		{
			if (access(path, X_OK) == 0)
				return (_strdup(path));
			perror(path);
		}
	}
	return (NULL);
}

/**
 * handle_path - checks if command is a direct path and executes it
 * @args: array of command arguments
 * @_env: environment variables
 *
 * Return: 1 if command was executed, 0 otherwise
 */
int handle_path(char **args, char **_env)
{
	char *fullpath, *old;

	if (!args || !args[0])
		return (0);

	fullpath = is_direct_executable(args[0]);
	if (fullpath)
	{
		old = args[0];
		args[0] = fullpath;
		command(args, _env);
		args[0] = old;
		free(fullpath);
		return (1);
	}

	return (0);
}
