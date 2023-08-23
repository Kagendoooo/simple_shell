#include "shell.h"

/**
 * _strlen - Returns length of string
 * @s: pointer to characters string
 * Return: length of character string
 */
int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len]; len)
		;
	return (len);
}

/**
 * _strcpy - Copies string
 * @dest: destination
 * @src: source
 * Return: Pointer to dest.
*/
char *_strcpy(char *dest, const char *src)
{
	size_t x;

	for (x = 0; src[x] != '\0'; x++)
		dest[x] = src[x];
	dest[x] = '\0';
	return (dest);
}
