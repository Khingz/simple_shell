#include "shell.h"

node_t *add_node_end(node_t **head, char *dir)
{
	node_t *new_node = malloc(sizeof(node_t));
	node_t *last;

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

node_t *get_dir(char *path)
{
	int idx;
	char **dirs;
	node_t *head;
	char *tmp_path;
       
	tmp_path = malloc(strlen(path) + 1);
	if (tmp_path)
		return (NULL);
	_strcpy(tmp_path, path);
	head = NULL;
	dirs = handle_split(tmp_path, ":");
	if (!dirs)
	{
		free(tmp_path);
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
	free(tmp_path);
	free(dirs);
	return (head);
}

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
