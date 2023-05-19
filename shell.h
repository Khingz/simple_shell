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
#include <errno.h>

extern char **environ;

/** STRUCTURES */

/**
 * struct node -  new struct type that defines a linked list.
 * @dir: directory path.
 * @next: pointer to another struct list_s.
 */
typedef struct node {
	struct node *next;
	char *dir;
} node_t;

/**
 * struct builtin_s - A structure type defining all builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv);
} builtin_t;

/* function prototypes */
char *get_env(const char *name);
int set_env(const char *name, const char *value, int overwrite);
int unset_env(const char *name);
node_t *get_dir(char *path);
char *get_loc(char *cmd);
node_t *add_node_end(node_t **head, char *dir);
void free_list(node_t *head);
char **handle_split(char *line, char *delim);
char **clear_input(char **argv);
int exec(char **arg, char *name, int hist);
int create_err(char *name, int hist, char *args, int error);
int execute_args(char **argv, char *name, int *hist);
int _get_args(char **argv);
void handle_signal(int signal);

/** string helper funcions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Error helpers */
int num_length(int num);
char *_itoa(int num);
char *err_2(char *name, int hist, char **argv);
char *err_126(char *name, int hist, char **argv);
char *err_127(char *name, int hist, char **argv);

#endif
