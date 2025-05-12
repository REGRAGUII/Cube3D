/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:09:53 by yregragu          #+#    #+#             */
/*   Updated: 2025/05/12 22:10:15 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wall_hit_point(t_img *img, t_ray *ray, int col, double perp_wall_dist)
{
	int	flag;
	int	flag0;

	if (ray->step_x < 0)
		flag = 0;
	else
		flag = 1;
	if (ray->step_y < 0)
		flag0 = 0;
	else
		flag0 = 1;
	if (ray->side == 0)
	{
		img->hit_x[col] = ray->map_x + flag;
		img->hit_y[col] = img->player_y + perp_wall_dist * sin(ray->angle);
	}
	else
	{
		img->hit_x[col] = img->player_x + perp_wall_dist * cos(ray->angle);
		img->hit_y[col] = ray->map_y + flag0;
	}
}
