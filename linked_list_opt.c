#include "shell.h"

/**
 * add_node_end - func that adds a new node to the end of a linked list.
 * @head: pointer to the head of the node_t
 * @dir: directory path for the new node to contain.
 * Return: returns pointer to the new node or NULL.
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
 * get_dir - func of token to a colon-separated list of dir into a linked list.
 * @path: points to colon-separated list of dir.
 * Return: returns pointer to the initial linked list.
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
 * @head: points to  head of node_t.
 * Return: no return value.
 **/
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
 * populate_path_dir - func that moves path and replaces leading/sandwiched/
 * trailing colons (:) with CWD
 * path: pointer
 * Return: no return value
 **/
char *populate_path_dir(char *path)
{
	int i, len;
	char *tmp_path, *pwd;

	len = 0;
	pwd = *(_get_env("PWD")) + 4;
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

/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *add_aliase_end(alias_t **head, char *name, char *val)
{
	alias_t *end;
	alias_t *new_node;
	
	new_node = malloc(sizeof(alias_t));
	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = val;
	_strcpy(new_node->name, name);

	if (*head)
	{
		end = *head;
		while (end->next != NULL)
			end = end->next;
		end->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void free_aliase_list(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}
