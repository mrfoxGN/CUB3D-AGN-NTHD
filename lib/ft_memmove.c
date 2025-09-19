/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:23:15 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 21:00:30 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest == src)
		return ((void *)dest);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (s < d)
	{
		while (size--)
			*(d + size) = *(s + size);
	}
	else
	{
		while (size--)
		{
			*d = *s;
			d++;
			s++;
		}
	}
	return (dest);
}
