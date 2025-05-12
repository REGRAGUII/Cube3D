/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:07:56 by yregragu          #+#    #+#             */
/*   Updated: 2025/05/11 06:48:41 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_textures(void *mlx, t_img *wall_textures, int count)
{
	int	i;

	i = 0;
	if (wall_textures)
	{
		while (i < count)
		{
			if (wall_textures[i].img_ptr)
				mlx_destroy_image(mlx, wall_textures[i].img_ptr);
			i++;
		}
		free(wall_textures);
	}
}

void	free_all(t_data *data)
{
	if (!data || !data->img)
		return ;
	if (data->img->img_ptr)
		mlx_destroy_image(data->img->mlx, data->img->img_ptr);
	if (data->img->win)
		mlx_destroy_window(data->img->mlx, data->img->win);
	if (data->img->mlx)
	{
		mlx_destroy_display(data->img->mlx);
		free(data->img->mlx);
	}
	if (data->img->key)
		free(data->img->key);
	if (data->img->ray_distances)
		free(data->img->ray_distances);
	if (data->img->ray_angles)
		free(data->img->ray_angles);
	if (data->img->wall_directions)
		free(data->img->wall_directions);
	free(data->img);
}

int	end(t_data *data)
{
	free_textures(data->img->mlx, data->wall_textures, 4);
	free_all(data);
	free_map(data->map_struct);
	free(data->content);
	free(data);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		end(data);
	if (keycode == 65361)
		data->img->key[130] = 1;
	if (keycode == 65363)
		data->img->key[131] = 1;
	if (keycode <= 127)
		data->img->key[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode <= 127)
		data->img->key[keycode] = 0;
	if (keycode == 65361)
		data->img->key[130] = 0;
	if (keycode == 65363)
		data->img->key[131] = 0;
	return (0);
}
