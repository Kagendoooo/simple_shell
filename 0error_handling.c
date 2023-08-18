#include "shell.h"

/**
  *num_len - finds digit length of number
  *@num: integer value
  *Return: digit's length
  */

int num_len(int num)
{
	unsigned int x;
	int len = 1;

	if (num < 0)
	{
		len++;
		x = num * -1;
	}
	else
	{
		x = num;
	}

	while (x > 9)
	{
		len++;
		x /= 10;
	}
	return (len);
}

