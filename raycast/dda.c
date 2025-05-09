/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:36:17 by yregragu          #+#    #+#             */
/*   Updated: 2025/05/09 02:38:26 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray_direction(t_img *img, int col, t_ray *ray)
{
	ray->angle = img->player_angle - (FOV_ANGLE / 2.0)
		+ (FOV_ANGLE * col / WIDTH);
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	ray->map_x = (int)img->player_x;
	ray->map_y = (int)img->player_y;
	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

void	init_step_side_dist(t_img *img, t_ray *ray)
{
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	if (ray->step_x < 0)
		ray->side_dist_x = (img->player_x - ray->map_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - img->player_x)
			* ray->delta_dist_x;
	if (ray->step_y < 0)
		ray->side_dist_y = (img->player_y - ray->map_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - img->player_y)
			* ray->delta_dist_y;
}

void	cast_ray_to_wall(char **map, t_ray *ray)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	ray->side = side;
}

void	calc_wall_dist_dir(t_img *img, t_ray *ray, int col)
{
	double	perp_wall_dist;	

	if (ray->side == 0)
		perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	img->ray_distances[col] = perp_wall_dist
		* cos(ray->angle - img->player_angle);
	img->ray_angles[col] = ray->angle;
	if (ray->side == 0)
	{
		if (ray->step_x < 0)
			img->wall_directions[col] = 'W';
		else
			img->wall_directions[col] = 'E';
	}
	else
	{
		if (ray->step_y < 0)
			img->wall_directions[col] = 'N';
		else
			img->wall_directions[col] = 'S';
	}
}

void	draw_view_ray(t_img *img, char **map)
{
	int		col;
	t_ray	ray;	

	col = 0;
	while (col < WIDTH)
	{
		init_ray_direction(img, col, &ray);
		init_step_side_dist(img, &ray);
		cast_ray_to_wall(map, &ray);
		calc_wall_dist_dir(img, &ray, col);
		col++;
	}
}
