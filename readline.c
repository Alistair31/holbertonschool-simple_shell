#include "man.h"

int main(void)
{
	size_t line = 0;
	char *str = NULL;
	ssize_t nread;

	while (1)
	{
		printf("$ ");
		nread = getline(&str, &line, stdin);

		if (nread == -1)
		{
			free(str);
			return (-1);
		}

		printf("%s", str);
	}
	free(str);
	return (0);
}
