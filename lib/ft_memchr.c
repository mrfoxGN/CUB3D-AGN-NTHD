/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:03:03 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 15:37:49 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (num > 0)
	{
		if (*p == (unsigned char)value)
			return ((void *)p);
		p++;
		num--;
	}
	return (NULL);
}
