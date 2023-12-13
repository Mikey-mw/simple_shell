#include "shell.h"

/**
 * split_str - splits a string into words. Repeat delimiters are ignored
 * @s: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_str(char *s, char *d)
{
	int i, j, k, m, n = 0;
	char **r;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!is_delim(s[i], d) && (is_delim(s[i + 1], d) || !s[i + 1]))
			n++;

	if (n == 0)
		return (NULL);
	r = malloc((1 + n) * sizeof(char *));
	if (!r)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (is_delim(s[i], d))
			i++;
		k = 0;
		while (!is_delim(s[i + k], d) && s[i + k])
			k++;
		r[j] = malloc((k + 1) * sizeof(char));
		if (!r[j])
		{
			for (k = 0; k < j; k++)
				free(r[k]);
			free(r);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			r[j][m] = s[i++];
		r[j][m] = 0;
	}
	r[j] = NULL;
	return (r);
}

/**
 * split_str2 - splits a string into words
 * @s: the input string
 * @c: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_str2(char *s, char c)
{
	int i, j, k, m, n = 0;
	char **r;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != c && s[i + 1] == c) ||
		    (s[i] != c && !s[i + 1]) || s[i + 1] == c)
			n++;

	if (n == 0)
		return (NULL);
	r = malloc((1 + n) * sizeof(char *));
	if (!r)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (s[i] == c && s[i] != c)
			i++;
		k = 0;
		while (s[i + k] != c && s[i + k] && s[i + k] != c)
			k++;
		r[j] = malloc((k + 1) * sizeof(char));
		if (!r[j])
		{
			for (k = 0; k < j; k++)
				free(r[k]);
			free(r);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			r[j][m] = s[i++];
		r[j][m] = 0;
	}
	r[j] = NULL;
	return (r);
}
