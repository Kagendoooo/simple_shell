#include "shell.h"
/**
 * _strtok - Tokenizes a string
 * @line: The string to be tokenized
 * @deli: The deliiter character to tokenize the string by
 * Return: A pointer to an array containing the tokenized words
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
