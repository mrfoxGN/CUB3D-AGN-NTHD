/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:23:26 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 20:58:22 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest == src)
		return ((void *)dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (size--)
	{
		*(d++) = *(s++);
	}
	return (dest);
}
