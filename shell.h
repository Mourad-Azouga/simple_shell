#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define _GNU_SOURCE
#include <signal.h>
#include <errno.h>
extern char **environ;
#include <limits.h>
#define TRUE 1
#define FALSE 0

/*SHELL.C*/
void execute(char **exe, char **envv);
char *pathfinder(char *input);
void forky(char **arg, char **ennv);

/*STRING.c*/
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *s);

/*PRINT.C*/
void print_env(void);
int _putchar(int c);
void _puts(char *str);

/*GETENV.C*/
char *_getenv(const char *name);

#endif /*SHELL_H*/
