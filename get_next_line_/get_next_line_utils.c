/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:48:36 by anguenda          #+#    #+#             */
/*   Updated: 2025/03/19 16:03:44 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr1(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strleen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_malloc(size_t count, size_t size)
{
	char	*ptr;

	if (!count || !size)
		return (NULL);
	if (size != 0 && size > (SIZE_MAX / count))
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*d;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strleen((char *)s);
	d = ft_malloc(sizeof(char) * (len + 1), 1);
	if (!d)
		return (NULL);
	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strjoiin(char *s1, char *s2)
{
	int		i;
	char	*d;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_strdup("");
	d = ft_malloc(sizeof(char) * (ft_strleen(s1) + ft_strleen(s2) + 1), 1);
	if (!d)
		return (free(s1), NULL);
	if (s1)
		while (s1[i])
			d[j++] = s1[i++];
	j = 0;
	while (s2[j])
	{
		d[i + j] = s2[j];
		j++;
	}
	d[i + j] = '\0';
	return (free(s1), d);
}
