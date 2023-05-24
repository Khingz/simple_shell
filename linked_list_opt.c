ii#include "shell.h"

/**
 * add_node_end - adds a new node to the end of a  linked list.
 * @head: pointer to the head of the node_t
 * @dir: directory path for the new node to contain.
 * Return: pointer to the new node or NULL.
 */
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
       
	tmp_path = malloc(_strlen(path) + 1);
	if (!tmp_path)
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
