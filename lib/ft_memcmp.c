/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:50:32 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/10 11:51:57 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *first, const void *second, size_t num)
{
	unsigned char	*f;
	unsigned char	*s;

	f = (unsigned char *)first;
	s = (unsigned char *)second;
	while (num > 0)
	{
		if (*f != *s)
			return (*f - *s);
		f++;
		s++;
		num--;
	}
	return (0);
}
