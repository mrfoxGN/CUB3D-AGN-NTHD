/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:06:49 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 22:46:26 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_inset(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;
	char	*trim_start;

	if (s == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s));
	start = 0;
	end = ft_strlen(s);
	while (s[start] && is_inset(set, s[start]))
		start++;
	while (end > start && is_inset(set, s[end - 1]))
		end--;
	trim = (char *)malloc((end - start + 1) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	trim_start = trim;
	while (start < end)
		*trim++ = s[start++];
	*trim = '\0';
	return (trim_start);
}
