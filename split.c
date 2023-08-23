#include "shell.h"

int token_len(char *str, char *deli);

/**
 * token_len - Locates the delimiter index
 * @str: string to be searched
 * @deli: delimiter character
 * Return: delimiter index
*/
int token_len(char *str, char *deli)
{
	int idx = 0, length = 0;

	while (*(str + idx) && *(str + idx) != *deli)
	{
		length++;
		idx++;
	}

	return (length);
}

/**
 * _strtok - Tokenize a string
 * @line: string to be tokenized
 * @deli: delimiter character to tokenize
 * Return: pointer
*/
char **_strtok(char *line, char *deli)
{
	char **ptr;
	int idx = 0, tkns, t, lttrs, l;

	tkns = count_tokens(line, deli);
	if (tkns == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tkns + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tkns; t++)
	{
		while (line[idx] == *deli)
			idx++;

		lttrs = token_len(line + idx, deli);

		ptr[t] = malloc(sizeof(char) * (lttrs + 1));
		if (!ptr[t])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(ptr[idx]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < lttrs; l++)
		{
			ptr[t][l] = line[idx];
			idx++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
