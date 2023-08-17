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

char **_strtok(char *line, char *deli);
char *get_location(char *command);
int _setenv(char **args, char __attribute__((__unused__)) **frt);
int _unsetenv(char **args, char __attribute__((__unused__)) **frt);
char **_getenv(const char *var);
char *get_location(char *command);
list_t *get_path_dir(char *path);

void free_list(list_t *head);
list_t *add_node_end(list_t **head, char *dir);

#endif
