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
 * struct node - struct type that defines a linked list.
 * @dir: directory path of a linked list.
 * @next: pointer to the head of the struct list_s.
 */
typedef struct node {
	struct node *next;
	char *dir;
} node_t;

/**
 * struct builtin_s - structure type defines all builtin commands.
 * @name: name of the builtin command.
 * @f: funct pointing to the command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **begin);
} builtin_t;

/**
 * struct alias_s -  new struct that defines aliases.
 * @name: name assigned to the alias.
* @value: value assigned to the alias.
 * @next: pointer to  struct alias_s.
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
int _handle_args(int *exe_ex_val);
char *_get_args(char *line, int *exe_ex_val);
int _call_args(char **args, char **begin, int *exe_ex_val);
int _check_args(char **argv);
void _handle_line(char **line, ssize_t read);
ssize_t _get_new_len(char *line);
void _logical_ops(char *line, ssize_t *len);
void handle_signal(int signal);
char **_copy_env(void);
void free_env(void);
char *populate_path_dir(char *path);
char **_get_env(const char *name);
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
char *err_cd(char **argv);
char *err_env(char **argv);
char *err_syntax(char **argv);

/* Builtin */
int exit_shell(char **argv, char **begin);
int (*_getbuiltin(char *cmd))(char **argv, char **begin);

/* Var replacement */
char *_get_env_val(char *proximal, int len);
void _replace_var(char **line, int *exe_ex_val);
char *_get_current_pid(void);
void free_args(char **args, char **begin);

/* get line */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void reassign_lineptr(char **lineptr, size_t *n, char *buff, size_t x);

/* aliase  */
char **_substi_aliases(char **argv);
int _alias(char **argv, char __attribute__((__unused__)) **head);
void _print_aliase(alias_t *alias);
void _set_aliase(char *name, char *val);
alias_t *add_aliase_end(alias_t **head, char *name, char *val);
int _help_builtin(char **argv, char __attribute__((__unused__)) **begin);
void free_aliase_list(alias_t *head);

/* help */
void general_help(void);
void aliase_help(void);
void cd_help(void);
void exit_help(void);
void help_help(void);
void env_help(void);
void set_env_help(void);
void unset_env_help(void);
/*void hist_help(void);*/

#endif
