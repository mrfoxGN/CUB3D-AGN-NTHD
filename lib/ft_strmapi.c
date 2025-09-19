/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:03:47 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/10 11:51:05 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	res_len;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	res_len = ft_strlen(s);
	result = (char *)malloc((res_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
