#include "shell.h"

int num_length(int num)
{
	int len = 1;

	while (num > 9)
	{
		len++;
		num /= 10;
	}

	return (len);
}

char *_itoa(int num)
{
	char *buff;
	int len;
		
	len = num_length(num);
	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	buff[len] = '\0';
	len--;
	while (len >= 0)
	{
		buff[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (buff);
}
