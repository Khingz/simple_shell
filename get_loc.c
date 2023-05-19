#include "shell.h"

/**
 * get_loc - func that locates a command in the PATH.
 * @cmd: command to locate in the PATH.
 * Return: name of PATH or NULL.
 */
char *get_loc(char *cmd)
{
	node_t *head, *_dirs;
	struct stat st;
	char *tmp, **path;

	path = get_env("PATH");
	if (!path && !(*path))
		return (NULL);
	_dirs = get_dir(path + 5);
	head = _dirs;
	while (_dirs)
	{
		tmp = malloc(_strlen(_dirs->dir) + 1 + _strlen(cmd) + 1);
		if (!tmp)
			return (NULL);
		_strcpy(tmp, _dirs->dir);
		_strcat(tmp, "/");
		_strcat(tmp, cmd);
		if (stat(tmp, &st) == 0)
		{
			free_list(head);
			return (tmp);
		}
		_dirs = _dirs->next;
		free(tmp);
	}
	free_list(head);
	return (NULL);
}
