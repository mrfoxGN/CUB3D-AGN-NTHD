/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:40:57 by ntahadou          #+#    #+#             */
/*   Updated: 2026/01/01 15:09:54 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/cube3d.h"

void	*ft_calloc(size_t nbr_elm, size_t elm_size)
{
	void	*ptr;
	size_t	total_size;

	if (elm_size && nbr_elm > SIZE_MAX / elm_size)
		return (NULL);
	else
		total_size = nbr_elm * elm_size;
	ptr = gc_malloc(total_size, 1);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
