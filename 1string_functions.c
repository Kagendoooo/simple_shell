#include "shell.h"

char *_strchr(char *s, char c);

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

int _strspn(char *s, char *accept);

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

int _strcmp(char *s1, char *s2);

/**
 * _strcmp - Compares two strings
 * @s1: first string
 * @s2: second string
 * Return: byte difference
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strncmp - Compare two strings
 * @s1: Pointer to string 1
 * @s2: Pointer to string 2
 * @n: first n bytes of strings to compare
 * Return: Less than 0 or Greater than 0
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t x;

	for (x = 0; s1[x] && s2[x] && x < n; x++)
	{
		if (s1[x] > s2[x])
			return (s1[x] - s2[x]);
		else if (s1[x] < s2[x])
			return (s1[x] - s2[x]);
	}
	if (x == n)
		return (0);
	else
		return (-15);
}
