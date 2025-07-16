/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:11:02 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/15 18:59:22 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	skip_word(const char *s, char sep)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (s[i] && (s[i] == sep))
		i++;
	while (s[i])
	{
		if (!quote && is_quote(s[i]))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else if (!quote && s[i] == sep)
			break ;
		i++;
	}
	return (i);
}

static char	*get_word(const char *s, int len)
{
	char	*word;
	int		i;
	int		j;
	char	quote;

	word = malloc(len + 1);
	i = 0;
	j = 0;
	quote = 0;
	if (!word)
		return (NULL);
	while (i < len)
	{
		if (!quote && is_quote(s[i]))
			quote = s[i++];
		else if (quote && s[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			word[j++] = s[i++];
	}
	word[j] = '\0';
	return (word);
}

static int	count_words(const char *s)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			len = skip_word(&s[i], ' ');
			count++;
			i += len;
		}
		else
			i++;
	}
	return (count);
}

char	**ft_split_cmd(const char *s)
{
	int		len;
	int		count;
	char	**result;

	count = count_words(s);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	count = 0;
	while (*s)
	{
		if (*s != ' ')
		{
			len = skip_word(s, ' ');
			result[count++] = get_word(s, len);
			s += len;
		}
		else
			s++;
	}
	result[count] = NULL;
	return (result);
}
