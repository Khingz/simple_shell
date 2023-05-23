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
#include <fcntl.h>
#define END_OF_FILE -2
#define EXIT -3
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
	int (*f)(char **argv, char **begin);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Globals */
alias_t *aliases;
char *name;
int hist;

/* function prototypes */
node_t *get_dir(char *path);
char *get_loc(char *cmd);
node_t *add_node_end(node_t **head, char *dir);
void free_list(node_t *head);
char **handle_split(char *line, char *delim);
char **clear_input(char **argv);
int exec(char **arg, char **begin);
int create_err(char **argv, int error);
int _run_args(char **argv, char **begin, int *exe_ex_val);
int handle_args(int *exe_ex_val);
char *get_args(char *line, int *exe_ex_val);
int call_args(char **args, char **begin, int *exe_ex_val);
int check_args(char **args);
void _handle_line(char **line, ssize_t read);
ssize_t _get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);
void handle_signal(int signal);
char **copy_env(void);
void free_env(void);
char *populate_path_dir(char *path);
char **get_env(const char *name);
int set_env(char **args, char __attribute__((__unused__)) **begin);
int unset_env(char **args, char __attribute__((__unused__)) **begin);
int ch_cd(char **args, char __attribute__((__unused__)) **begin);
void space_handler(char **line, ssize_t read);
int print_env(char **args, char __attribute__((__unused__)) **begin);


/** string helper funcions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int process_file_cmd(char *file_path);


/* Error helpers */
int num_length(int num);
char *_itoa(int num);
char *err_exit(char **argv);
char *err_126(char **argv);
char *err_127(char **argv);
char *err_cd(char **args);
char *err_env(char **args);
char *err_syntax(char **args);
char *error_1(char **args);

/* Builtin */
int exit_shell(char **argv, char **begin);
int (*_getbuiltin(char *cmd))(char **argv, char **begin);

/* Var replacement */
char *get_env_val(char *proximal, int len);
void replace_var(char **line, int *exe_ex_val);
char *get_current_pid(void);
void free_args(char **args, char **begin);

/* get line */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void reassign_lineptr(char **lineptr, size_t *n, char *buff, size_t x);

/* aliase  */
char **substi_aliases(char **argv);
int _alias(char **argv, char __attribute__((__unused__)) **head);
void print_aliase(alias_t *alias);
void set_aliase(char *name, char *val);
alias_t *add_aliase_end(alias_t **head, char *name, char *val);
int builtin_help(char **args, char __attribute__((__unused__)) **front);
void free_aliase_list(alias_t *head);

/* help */
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

#endif
