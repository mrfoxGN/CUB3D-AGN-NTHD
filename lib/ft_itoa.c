/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:35:32 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/09 12:18:32 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_n(long n, int sign)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		count++;
	}
	if (sign == -1)
		return (count + 1);
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		sign;
	long	nb;
	int		count;

	nb = n;
	sign = 1;
	if (nb < 0)
	{
		sign = -1;
		nb = -nb;
	}
	count = count_n(nb, sign);
	result = (char *)malloc((count + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[count] = '\0';
	while (count > 0)
	{
		result[--count] = (nb % 10) + '0';
		nb /= 10;
	}
	if (sign == -1)
		result[0] = '-';
	return (result);
}
