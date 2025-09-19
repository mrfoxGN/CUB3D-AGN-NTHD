/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:29:04 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/10 11:50:59 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *word, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (word[0] == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (word[j])
		{
			if (str[i + j] == word[j] && i + j < len)
				j++;
			else
				break ;
		}
		if (word[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
