#include "shell.h"
/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @deli: The deliiter character to tokenize the string by
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *deli)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(line, deli);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *deli)
			index++;

		letters = token_len(line + index, deli);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}

