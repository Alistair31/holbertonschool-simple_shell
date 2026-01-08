#ifndef MAN_H
#define MAN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

char **split_words(char *str);
char **split_line(int interactive);
int findcmd(char **args, char **_env, int last_status);
int command(char **args, char **_env);
char *get_path(char **_env);
char *find_executable_in_path(const char *cmd, char **_env);
char *is_direct_executable(const char *path);
char *build_fullpath(const char *dir, const char *cmd);
int handle_path(char **args, char **_env);
int search_path(char **args, char **_env);
int _builtin(char **args, char **_env);
void free_args(char **args);
int builtin_exit(char **args);
char **makeenv(char **envp);
int builtin_env(char **_env);
char *_strdup(const char *s);

#endif
