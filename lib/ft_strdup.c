/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:58:58 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/10 15:49:46 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	strlen;
	char	*cpy;

	strlen = ft_strlen(str) + 1;
	cpy = (char *)malloc(strlen * sizeof(char));
	if (cpy)
		ft_strlcpy(cpy, str, strlen);
	return (cpy);
}
