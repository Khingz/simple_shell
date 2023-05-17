#ifndef SHELL_H_
#define SHELL_H_

/* header files */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Structs */
typedef struct node {
	struct node *next;
	char *dir;
} node_t;

/* function prototypes */
char *get_env(const char *name);
int set_env(const char *name, const char *value, int overwrite);
int unset_env(const char *name);
node_t *get_path_dir(char *path);
char *get_loc(char *cmd);
node_t *add_node_end(node_t **head, char *dir);
void free_list(node_t *head);
char **handle_split(char *line, char *delim);

#endif
