/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:17:05 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 12:36:04 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t count)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)str;
	while (i < count)
	{
		ptr[i] = (unsigned char)value;
		i++;
	}
	return (str);
}
