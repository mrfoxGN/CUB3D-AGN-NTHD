/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:37:44 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 15:43:02 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	joinsize;
	char	*join;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	joinsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(joinsize * sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, joinsize + 1);
	return (join);
}
