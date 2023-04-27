#include "main.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter
 * @c: Character to check
 * @delim: Delimiter characters
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}


/**
 * _isalpha - Checks if a character is an alphabetic letter
 * @c: The character to be checked
 *
 * Return: 1 if c is a letter, 0 otherwise
 */
int _isalpha(int c)
{
	int i;

	/* Loop through the uppercase and lowercase letters in the ASCII table */
	for (i = 'A'; i <= 'Z'; i++)
	{
		if (c == i || c == i + 32)
			return (1);
	}

	return (0);
}


/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
