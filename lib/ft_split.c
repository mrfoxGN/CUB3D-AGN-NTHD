/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:07:40 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 21:00:04 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(const char *s, char c)
{
	size_t	count;
	char	s_start;

	if (!*s)
		return (0);
	count = 0;
	s_start = s[0];
	while (*s)
	{
		if (*s == c && (*(s + 1) != c && *(s + 1) != '\0'))
			count++;
		s++;
	}
	if (s_start != c)
		count++;
	return (count);
}

static void	ft_free(char **arr, int k)
{
	while (k > 0)
	{
		free(arr[--k]);
	}
	free(arr);
}

static char	*fill_word(const char *s, int start, int end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**split_words(const char *s, char c, char **arr)
{
	size_t	i;
	size_t	start;
	size_t	k;

	i = 0;
	k = 0;
	while (k < word_count(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		arr[k] = fill_word(s, start, i);
		if (!arr[k])
		{
			ft_free(arr, k);
			return (NULL);
		}
		k++;
	}
	arr[k] = NULL;
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	wordcount;

	if (s == NULL)
		return (NULL);
	wordcount = word_count(s, c);
	arr = (char **)malloc((wordcount + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (split_words(s, c, arr));
}
