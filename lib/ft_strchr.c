/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:24:41 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 15:41:17 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int sc)
{
	while (*str)
	{
		if (*str == (char)sc)
			return ((char *)str);
		str++;
	}
	if ((char)sc == '\0')
		return ((char *)str);
	return (NULL);
}
