#include "man.h"
/**
 * shellpath - constructs the full path of a command
 * @cmd: the command name
 * Return: full path of the command
 */
char *shellpath(char *cmd)
{
	char *libpath = "/usr/local/bin:/usr/bin:/sbin:/usr/sbin:";
	char *folderpath;
	char *foldtoken;
	char *path;

	folderpath = strdup(libpath);

	if (cmd == NULL || cmd[0] == '\0')
	{
		return (NULL);
	}
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			return (strdup(cmd));
		}
		return (NULL);
	}
	foldtoken = strtok(folderpath, ":");
	while (foldtoken != NULL)
	{
		path = malloc(strlen(foldtoken) + strlen(cmd) + 2);
		strcpy(path, foldtoken);
		strcat(path, "/");
		strcat(path, cmd);

		if (access(path, X_OK) == 0)
		{
			free(folderpath);
			return (path);
		}
		free(path);
		foldtoken = strtok(NULL, ":");
	}
	free(folderpath);
	return (NULL);
}
