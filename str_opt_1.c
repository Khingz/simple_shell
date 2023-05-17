#include "shell.h"

/**
 * _strlen - get length of a string.
 * @s: string char.
 * Return: len of string.
 */
int _strlen(const char *str)
{
	int len = 0;

	if (!str)
		return (len);
	for (len = 0; str[len]; len++)
		;
	return (len);
}

/**
 * _strcpy - Copies string from src to dest
 * @dest: string source
 * @src: string destination
 * Return: pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: destination string.
 * @src: string source
 * Return: Pointer to dest.
 */
char *_strcat(char *dest, const char *src)
{
	char *tmp_dest;
	const char *tmp_src;

	tmp_dest = dest;
	tmp_src =  src;

	while (*tmp_dest != '\0')
		tmp_dest++;

	while (*tmp_src != '\0')
		*tmp_dest++ = *tmp_src++;
	*tmp_dest = '\0';
	return (dest);
}

/**
 * _strncat - Concar n bytes of two strings
 * @dest: destination string.
 * @src: source string.
 * @n: n bytes to copy from src.
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
