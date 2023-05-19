#include "shell.h"

/**
 * add_node_end - adds a new node to the end of a  linked list.
 * @head: pointer to the head of the node_t
 * @dir: directory path for the new node to contain.
 * Return: pointer to the new node or NULL.
 */
node_t *add_node_end(node_t **head, char *dir)
{
	node_t *last;
	node_t *new_node;
       
	new_node = malloc(sizeof(node_t));
	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 * get_dir - takes token to a colon-separated list of dir into a linked list.
 * @path: colon-separated list of dir.
 * Return: pointer to the initial linked list.
 */
node_t *get_dir(char *path)
{
	int idx;
	char **dirs;
	node_t *head;
	char *tmp_path;
       
	head = NULL;
	tmp_path = populate_path_dir(path);
	if (!tmp_path)
		return (NULL);
	dirs = handle_split(tmp_path, ":");
	free(tmp_path);
	if (!dirs)
	{
		return (NULL);
	}
	for (idx = 0; dirs[idx]; idx++)
	{
		if (add_node_end(&head, dirs[idx]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}	
	}
	free(dirs);
	return (head);
}

/**
 * free_list - func that frees a linked list.
 * @head: pointer to  head of node_t.
 */
void free_list(node_t *head)
{
	node_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}

/**
 * populate_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory
 */
char *populate_path_dir(char *path)
{
	int i, len;
	char *tmp_path, *pwd;

	len = 0;
	pwd = *(get_env("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	tmp_path = malloc(sizeof(char) * (len + 1));
	if (!tmp_path)
		return (NULL);
	tmp_path[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(tmp_path, pwd);
				_strcat(tmp_path, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(tmp_path, ":");
				_strcat(tmp_path, pwd);
			}
			else
				_strcat(tmp_path, ":");
		}
		else
		{
			_strncat(tmp_path, &path[i], 1);
		}
	}
	return (tmp_path);
}
