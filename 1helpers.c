#include "shell.h"

/**
  *format_line - partitions a line from std input
  *@line: a pointer to line
  *@read: length of line
  */

void format_line(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char prev, curr, next;
	size_t x, y;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	y = 0;
	old_line = *line;
	for (x = 0; old_line[x]; x++)
	{
		curr = old_line[x];
		next = old_line[x + 1];
		if (x != 0)
		{
			prev = old_line[x - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					new_line[y++] = ' ';
					new_line[y++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					new_line[y++] = ';';
					new_line[y++] = ' ';
					continue;
				}
				if (prev != ' ')
					new_line[y++] = ' ';
				new_line[y++] = ';';
				if (next != ' ')
					new_line[y++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
					new_line[y++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					new_line[y++] = '&';
					new_line[y++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
					new_line[y++] = ' ';
				else if (prev == '|' && next != ' ')
				{
					new_line[y++] = '|';
					new_line[y++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (x != 0 && old_line[x - 1] != ' ')
				new_line[y++] = ' ';
			new_line[y++] = ';';
			if (next != ' ' && next != ';')
				new_line[y++] = ' ';
			continue;
		}
		new_line[y++] = old_line[x];
	}
	new_line[y] = '\0';
	free(*line);
	*line = new_line;
}

/**
  *get_new_len - get new len of line
  *@line: line to check
  *Return: new len
  */

ssize_t get_new_len(char *line)
{
	size_t x;
	ssize_t new_len = 0;
	char curr, next;

	for (x = 0; line[x]; x++)
	{
		curr = line[x];
		next = line[x + 1];
		if (curr == '#')
		{
			if (x == 0 || line[x - 1] == ' ')
			{
				line[x] = '\0';
				break;
			}
		}
		else if (x != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && line[x - 1] != ' ' && line[x - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[x - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[x - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[x], &new_len);
		}
		else if (curr == ';')
		{
			if (x != 0 && line[x - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
  *logical_ops - checks a line for logical operators
  *@line: pointer to character in line
  *@new_len: pointer to new_len
  */

void logical_ops(char *line, ssize_t *new_len)
{
	char prev, curr, next;

	prev = *(line - 1);
	curr = *line;
	next = *(line + 1);

	if (curr == '&')
	{
		if (next == '&' && prev != ' ')
			(*new_len)++;
		else if (prev == '&' && next != ' ')
			(*new_len)++;
	}
	else if (curr == '|')
	{
		if (next == '|' && prev != ' ')
			(*new_len)++;
		else if (prev == '|' && next != ' ')
			(*new_len)++;
	}
}

