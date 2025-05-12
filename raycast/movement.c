/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:13:25 by yregragu          #+#    #+#             */
/*   Updated: 2025/05/12 20:03:36 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	move_front(t_data *data)
{
	double	next_x;
	double	next_y;

	if (data->img->key['w'])
	{
		next_x = data->img->player_x
			+ cos(data->img->player_angle) * PLAYER_SPEED;
		next_y = data->img->player_y
			+ sin(data->img->player_angle) * PLAYER_SPEED;
		if (data->content[(int)(next_y)][(int)(next_x)] != '1')
		{
			data->img->player_x = next_x;
			data->img->player_y = next_y;
		}
	}
}

static void	move_back(t_data *data)
{
	double	next_x;
	double	next_y;

	if (data->img->key['s'])
	{
		next_x = data->img->player_x
			- cos(data->img->player_angle) * PLAYER_SPEED;
		next_y = data->img->player_y
			- sin(data->img->player_angle) * PLAYER_SPEED;
		if (data->content[(int)(next_y)][(int)(next_x)] != '1')
		{
			data->img->player_x = next_x;
			data->img->player_y = next_y;
		}
	}
}

static void	move_right(t_data *data)
{
	double	next_x;
	double	next_y;

	if (data->img->key['d'])
	{
		next_x = data->img->player_x
			+ cos(data->img->player_angle + PI / 2) * PLAYER_SPEED;
		next_y = data->img->player_y
			+ sin(data->img->player_angle + PI / 2) * PLAYER_SPEED;
		if (data->content[(int)(next_y)][(int)(next_x)] != '1')
		{
			data->img->player_x = next_x;
			data->img->player_y = next_y;
		}
	}
}

static void	move_left(t_data *data)
{
	double	next_x;
	double	next_y;

	if (data->img->key['a'])
	{
		next_x = data->img->player_x - cos(data->img->player_angle + PI / 2)
			* PLAYER_SPEED;
		next_y = data->img->player_y - sin(data->img->player_angle + PI / 2)
			* PLAYER_SPEED;
		if (data->content[(int)(next_y)][(int)(next_x)] != '1')
		{
			data->img->player_x = next_x;
			data->img->player_y = next_y;
		}
	}
}

int	move_player(t_data *data)
{
	data->img->ceiling_color = get_color(data->ceiling_r,
			data->ceiling_g, data->ceiling_b);
	data->img->floor_color = get_color(data->floor_r,
			data->floor_g, data->floor_b);
	if (data->img->key[130])
		data->img->player_angle -= 0.05;
	if (data->img->key[131])
		data->img->player_angle += 0.05;
	if (data->img->player_angle < 0)
		data->img->player_angle += 2 * PI;
	if (data->img->player_angle > 2 * PI)
		data->img->player_angle -= 2 * PI;
	move_front(data);
	move_back(data);
	move_right(data);
	move_left(data);
	mlx_destroy_image(data->img->mlx, data->img->img_ptr);
	data->img->img_ptr = mlx_new_image(data->img->mlx, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img_ptr, &data->img->bpp,
			&data->img->size_line, &data->img->endian);
	draw(data, data->img);
	mlx_put_image_to_window(data->img->mlx,
		data->img->win, data->img->img_ptr, 0, 0);
	return (0);
}
