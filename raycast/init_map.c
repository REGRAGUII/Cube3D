/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:30:42 by youssef           #+#    #+#             */
/*   Updated: 2025/05/09 03:32:05 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw(t_data *data, t_img *img)
{
	draw_view_ray(img, data->content);
	draw_3d_walls(data);
}

void	xpm_failed(t_data *data, char *str, int i)
{
	ft_putstr_fd("Error: Failed to load texture: ", 2);
	ft_putendl_fd(str, 2);
	free_textures(data->img->mlx, data->wall_textures, i);
	free_all(data);
	exit(EXIT_FAILURE);
}

void	texture_loading(t_data *data)
{
	char	*paths[4];
	int		i;

	paths[0] = data->no;
	paths[1] = data->so;
	paths[2] = data->ea;
	paths[3] = data->we;
	i = 0;
	while (i < 4)
	{
		data->wall_textures[i].img_ptr = mlx_xpm_file_to_image(data->img->mlx,
				paths[i], &data->wall_textures[i].width,
				&data->wall_textures[i].height);
		if (!data->wall_textures[i].img_ptr)
			xpm_failed(data, paths[i], i);
		data->wall_textures[i].addr = mlx_get_data_addr(
				data->wall_textures[i].img_ptr,
				&data->wall_textures[i].bpp,
				&data->wall_textures[i].size_line,
				&data->wall_textures[i].endian);
		i++;
	}
}

void	initialization(t_data *data)
{
	data->img = malloc(sizeof(t_img));
	data->img->key = malloc(sizeof(char) * 150);
	data->img->player_angle = 0.0;
	data->img->ray_distances = malloc(sizeof(double) * WIDTH);
	data->img->ray_angles = malloc(sizeof(double) * WIDTH);
	data->img->wall_directions = malloc(sizeof(char) * WIDTH);
	data->wall_textures = malloc(sizeof(t_img) * 4);
	ft_memset(data->img->key, 0, 150);
	ft_memset(data->img->ray_distances, 0, WIDTH);
	ft_memset(data->img->ray_angles, 0, WIDTH);
	data->img->mlx = mlx_init();
	data->img->win = mlx_new_window(
			data->img->mlx, WIDTH, HEIGHT, "Pinky & Brain");
	data->img->img_ptr = mlx_new_image(data->img->mlx, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img_ptr, &data->img->bpp,
			&data->img->size_line, &data->img->endian);
}

void	render(t_data *data)
{
	initialization(data);
	texture_loading(data);
	find_player_position(data);
	player_facing(data->img);
	mlx_hook(data->img->win, 17, 0, end, data);
	mlx_hook(data->img->win, 02, (1L << 0), key_press, data);
	mlx_hook(data->img->win, 03, (1L << 1), key_release, data);
	mlx_loop_hook(data->img->mlx, move_player, data);
	mlx_put_image_to_window(data->img->mlx,
		data->img->win, data->img->img_ptr, 0, 0);
	mlx_loop(data->img->mlx);
}
