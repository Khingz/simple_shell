#include "shell.h"

/**
 * replace_aliases -
 */
char **_substi_aliases(char **argv)
{
	alias_t *tmp;
	int i;
	char *new_val;

	if (!argv)
		return (NULL);
	for (i = 0; argv[i]; i++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(argv[i], tmp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
				if (!new_val)
				{
					free_args(argv, argv);
					return (NULL);
				}
				_strcpy(new_val, tmp->value);
				free(argv[i]);
				argv[i] = new_val;
				break;
			}
			tmp = tmp->next;
		}
	}

	return (argv);
}

/**
 * shellby_alias -
 */
int _alias(char **argv, char __attribute__((__unused__)) **head)
{
	alias_t *tmp;
	int i, ex_val;
	char *val;

	tmp = aliases;
	ex_val = 0;
	if (!argv[0])
	{
		while (tmp)
		{
			_print_aliase(tmp);
			tmp = tmp->next;
		}
		return (ex_val);
	}
	for (i = 0; argv[i]; i++)
	{
		tmp = aliases;
		val = _strchr(argv[i], '=');
		if (!val)
		{
			while (tmp)
			{
				if (_strcmp(argv[i], tmp->name) == 0)
				{
					_print_aliase(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				ex_val = create_err(argv + i, 1);
		}
		else
			_set_aliase(argv[i], val);
	}
	return (ex_val);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 */
void _set_aliase(char *name, char *val)
{
	alias_t *tmp;
	int len, j, k;
	char *new_val;

	tmp = aliases;
	*val = '\0';
	val++;
	len = _strlen(val) - _strspn(val, "'\"");
	new_val = malloc(sizeof(char) * (len + 1));
	if (!new_val)
		return;
	for (j = 0, k = 0; val[j]; j++)
	{
		if (val[j] != '\'' && val[j] != '"')
			new_val[k++] = val[j];
	}
	new_val[k] = '\0';
	while (tmp)
	{
		if (_strcmp(name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_val;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_aliase_end(&aliases, name, new_val);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 */
void _print_aliase(alias_t *alias)
{
	char *aliase_str;
	int len;
	
	len = _strlen(alias->name) + _strlen(alias->value) + 4;

	aliase_str = malloc(sizeof(char) * len);
	if (!aliase_str)
		return;
	_strcpy(aliase_str, alias->name);
	_strcat(aliase_str, "='");
	_strcat(aliase_str, alias->value);
	_strcat(aliase_str, "'\n");

	write(STDOUT_FILENO, aliase_str, len);
	free(aliase_str);
}
