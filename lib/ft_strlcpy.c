/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:39:00 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 15:47:55 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	srclen;

	srclen = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	while (size - 1 > 0 && *src)
	{
		*dest++ = *src++;
		size--;
	}
	*dest = '\0';
	return (srclen);
}
