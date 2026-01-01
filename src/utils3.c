/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:31:50 by anguenda          #+#    #+#             */
/*   Updated: 2026/01/01 10:51:28 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <fcntl.h>

void	close_fd_if_open(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	free_split_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_elemnts(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (0);
	while (arr[count])
		count++;
	return (count);
}

int	*fill_elements(char **arr)
{
	int	*values;
	int	i;

	values = gc_malloc(3 * sizeof(int), 1);
	if (!values)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		values[i] = 0;
		i++;
	}
	i = 0;
	while (arr && arr[i] && i < 3)
	{
		values[i] = ft_atoi(arr[i]);
		i++;
	}
	return (values);
}

int	rgb_values_valid(int *rgb)
{
	int	i;

	if (!rgb)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
	return (1);
}
