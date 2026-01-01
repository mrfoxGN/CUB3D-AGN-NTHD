/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 14:39:27 by ntahadou          #+#    #+#             */
/*   Updated: 2026/01/01 14:39:39 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_ray_seg(t_ray_seg *ray)
{
	int		steps;
	float	x;
	float	y;
	int		i;

	if (!ray || !ray->img)
		return ;
	if (fabs((ray->ex - ray->sx)) > fabs((ray->ey - ray->sy)))
		steps = (int)fabs((ray->ex - ray->sx));
	else
		steps = (int)fabs((ray->ey - ray->sy));
	x = ray->sx;
	y = ray->sy;
	i = 0;
	while (i <= steps)
	{
		x += (int)(ray->ex - ray->sx) / (float)steps;
		y += (int)(ray->ey - ray->sy) / (float)steps;
		my_mlx_pixel_put(ray->img, ray->color, (int)x, (int)y);
		i++;
	}
}

void	fill_window(t_game *game, int w, int h, int color)
{
	int	i;
	int	j;

	if (!game)
		return ;
	i = 0;
	j = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			my_mlx_pixel_put(&game->img, color, j, i);
			j++;
		}
		i++;
	}
}

void	draw_vertical_line(t_draw_line *params)
{
	int	i;

	if (!params || !params->img)
		return ;
	i = params->drawstart;
	while (i < params->drawend)
	{
		my_mlx_pixel_put(params->img, params->color, params->x, i);
		i++;
	}
}
