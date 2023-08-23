#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct node {
	struct node *next;
	char *dir;
} node_t;


int (*_builtin(char *command))(char **args, char **frt);
int shellby_exit(char **args, char **frt);
int shellby_cd(char **args, char __attribute__((__unused__)) **frt);
int shellby_help(char **args, char __attribute__((__unused__)) **frt);

int num_len(int num);
char *_itoa(int num);
int create_err(char **args, int err);

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

char *0err26(char **args);
char *0err27(char **args);

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size);
void assign_lnptr(char **lnptr, size_t *n, char *buff, size_t b);
ssize_t _getline(char **lnptr, size_t *n, FILE *strm);

int token_len(char *str, char *deli);
int count_tokens(char *str, char *deli);
char **_strtok(char *line, char *deli);

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);

void sig_handler(int sig);
int execute(char **args, char **frt);
int main(int argc, char *argv[]);

char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

int shellby_alias(char **args, char __attribute__((__unused__)) **frt);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

char *get_args(char *line, int *_exe);
int call_args(char **args, char **frt, int *_exe);
int exe_args(char **args, char **frt, int *_exe);
int format_args(int *_exe);
int check_args(char **args);

int shellby_env(char **args, char __attribute__((__unused__)) **frt);
int _setenv(char **args, char __attribute__((__unused__)) **frt);
int _unsetenv(char **args, char __attribute__((__unused__)) **frt);

void free_args(char **args, char **frt);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void replace_vars(char **args, int *_exe);

void format_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);


#endif
