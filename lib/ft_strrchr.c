/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:11:00 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/11 15:49:58 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int sc)
{
	char	*lastdotpos;

	lastdotpos = NULL;
	while (*str)
	{
		if (*str == (char)sc)
			lastdotpos = (char *)str;
		str++;
	}
	if ((char) sc == '\0')
		lastdotpos = (char *)str;
	return (lastdotpos);
}
