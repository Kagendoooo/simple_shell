#include "shell.h"
/**
 * _strchr - Locate a character in string
 * @s: string
 * @c: character to be located
 * Return: Pointer or NULL
*/
char *_strchr(char *s, char c)
{
	int idx;

	for (idx = 0; s[idx]; idx++)
	{
		if (s[idx] == c)
			return (s + idx);
	}

	return (NULL);
}

/**
 * _strspn - Gets the length of substring prefix
 * @s: string
 * @accept: prefix to be measured
 * Return: number of bytes in s
*/
int _strspn(char *s, char *accept)
{
	int b = 0;
	int idx;

	while (*s)
	{
		for (idx = 0; accept[idx]; idx++)
		{
			if (*s == accept[idx])
			{
				b++;
				break;
			}
		}
		s++;
	}
	return (b);
}
