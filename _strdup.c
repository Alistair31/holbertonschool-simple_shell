#include "man.h"

/**
 * _strdup - duplicates a string
 * @s: input string
 *
 * Return: pointer to duplicated string, or NULL on failure
 */
char *_strdup(const char *s)
{
    char *dup;
    size_t len;

    if (!s)
        return (NULL);

    len = strlen(s);
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);

    strcpy(dup, s);
    return (dup);
}
