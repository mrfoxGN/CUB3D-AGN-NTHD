/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:58:58 by ntahadou          #+#    #+#             */
/*   Updated: 2026/01/01 10:50:21 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/cube3d.h"

char	*ft_strdup(const char *str)
{
	size_t	strlen;
	char	*cpy;

	strlen = ft_strlen(str) + 1;
	cpy = (char *)gc_malloc(strlen * sizeof(char), 1);
	if (cpy)
		ft_strlcpy(cpy, str, strlen);
	return (cpy);
}
