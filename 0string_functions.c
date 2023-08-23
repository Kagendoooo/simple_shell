#include "shell.h"

int _strlen(const char *s);

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

char *_strcpy(char *dest, const char *src);

/**
 * _strcpy - Copies string
 * @dest: destination
 * @src: source
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t x;

	for (x = 0; src[x] != '\0'; x++)
		dest[x] = src[x];
	dest[x] = '\0';
	return (dest);
}

char *_strcat(char *dest, const char *src);

/**
 * _strcat - Concantenates two strings
 * @dest: destination
 * @src: source
 * Return: Pointer
*/

char *_strcat(char *dest, const char *src)
{
	char *a;
	const char *b;

	a = dest;
	b =  src;

	while (*a != '\0')
		a++;

	while (*b != '\0')
		*a++ = *b++;
	*a = '\0';
	return (dest);
}

char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strncat - Concantenates two strings
 * @dest: destination
 * @src: source
 * @n: bytes to copy
 * Return: Pointer
*/
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dlen = _strlen(dest);
	size_t z;

	for (z = 0; z < n && src[z] != '\0'; z++)
		dest[dlen + z] = src[z];
	dest[dlen + z] = '\0';

	return (dest);
}
