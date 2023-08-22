#include "shell.h"

void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size);

/**
 * _realloc - Reallocates a memory block
 * @ptr: A pointer to the memory
 * @prev_size: size of allocated space for ptr
 * @new_size: size of new memory block.
 * Return: pointer or NULL
*/
void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	void *memry;
	char *ptr_cpy, *fill;
	unsigned int idx;

	if (new_size == prev_size)
		return (ptr);

	if (ptr == NULL)
	{
		memry = malloc(new_size);
		if (memry == NULL)
			return (NULL);

		return (memry);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_cpy = ptr;
	memry = malloc(sizeof(*ptr_cpy) * new_size);
	if (memry == NULL)
	{
		free(ptr);
		return (NULL);
	}

	fill = memry;

	for (idx = 0; idx < prev_size && idx < new_size; idx++)
		fill[idx] = *ptr_cpy++;

	free(ptr);
	return (memry);
}


void assign_lnptr(char **lnptr, size_t *n, char *buff, size_t b);

/**
 * assign_lnptr - Reassigns the lnptr
 * @lnptr: A buffer to store input string
 * @n: size of lnptr
 * @buff: string to assign to lnptr
 * @b: size of buffer
*/
void assign_lnptr(char **lnptr, size_t *n, char *buff, size_t b)
{
	if (*lnptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lnptr = buff;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lnptr = buff;
	}
	else
	{
		_strcpy(*lnptr, buff);
		free(buff);
	}
}

ssize_t _getline(char **lnptr, size_t *n, FILE *strm);

/**
 * _getline - Reads input from a strm
 * @lnptr: buffer to store the input
 * @n: size of lnptr
 * @strm: strm to read from
 * Return: number of bytes read
*/
ssize_t _getline(char **lnptr, size_t *n, FILE *strm)
{
	static ssize_t in;
	ssize_t ret;
	char a = 'x', *buff;
	int b;

	if (in == 0)
		fflush(strm);
	else
		return (-1);
	in = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	while (a != '\n')
	{
		b = read(STDIN_FILENO, &c, 1);
		if (b == -1 || (b == 0 && in == 0))
		{
			free(buff);
			return (-1);
		}
		if (b == 0 && in != 0)
		{
			in++;
			break;
		}

		if (in >= 120)
			buff = _realloc(buff, in, in + 1);

		buff[in] = a;
		in++;
	}
	buff[in] = '\0';

	assign_lnptr(lnptr, n, buff, in);

	ret = in;
	if (b != 0)
		in = 0;
	return (ret);
}
