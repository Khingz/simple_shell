#include "shell.h"

int num_length(int num)
{
	int len = 1;
	unsigned int tmp_num;

	if (num < 0)
	{
		len++;
		tmp_num = num * -1;
	}
	else
	{
		tmp_num = num;
	}
	while (tmp_num > 9)
	{
		len++;
		tmp_num /= 10;
	}
	return (len);
}

char *_itoa(int num)
{
	char *buff;
	int len;
	unsigned int tmp_num;
		
	len = num_length(num);
	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	buff[len] = '\0';
	if (num < 0)
	{
		tmp_num = num * -1;
		buff[0] = '-';
	}
	else
	{
		tmp_num = num;
	}

	len--;
	do {
		buff[len] = (tmp_num % 10) + '0';
		tmp_num /= 10;
		len--;
	} while(tmp_num > 0);
	return (buff);
}
