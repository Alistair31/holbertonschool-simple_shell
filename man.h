#ifndef MAN_H
#define MAN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
char **split_words(char *str);
char **bunchwords(int interactive);

#endif
