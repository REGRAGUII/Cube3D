/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:30:42 by youssef           #+#    #+#             */
/*   Updated: 2025/05/08 19:20:39 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



int get_map_height(char **map)
{
	int i = 0;
	while (map[i])
		i++;
	return i;
}

int get_map_width(char *row)
{
	int i = 0;
	while (row[i])
		i++;
	return i;
}


void square(t_img *img, char pixel, int x, int y)
{
	int color;
	int	i;
	int	j;
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	int size = 30;
	i = 0;
	j = 0;
	start_x = x * size;
	start_y = y * size;
	end_x = start_x + size;
	end_y = start_y + size;
	
	if (pixel == '0')
	color = 0x00000000; 
	else if (pixel == '1')
	color = 0xFFFFFFFF; 
	i = start_x + 1;
	while(i < end_x-1)
	{
		j = start_y+1;
		while(j < end_y-1)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}





void player(t_img *img)
{
	int size = 64;
	int px= (int)(img->player_x * size);
	int py = (int)(img->player_y * size);
	int player_size = size /2;
	int i , j ;
	i = py ;
	while(i < py + player_size)
	{
		j = px ;
		while(j < px + player_size)
		{
			my_mlx_pixel_put(img, j, i, 0x0000FFFF);
			j++;
		}
		i++;
	}
}
void	draw(t_data *data, t_img *img)
{
	int i;
	int j;

	i = 0;
	while (data->content[i])
	{
		j = 0;
		while (data->content[i][j])
		{
			square(img, data->content[i][j], j, i);
			j++;
		}
		i++;
	}
	draw_view_ray(img, data->content);
	// player(img);
	draw_3d_walls(data);
	
}
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

void free_all(t_data *data)
{
	if (!data || !data->img)
		return;
	if(data->img->img_ptr)
		mlx_destroy_image(data->img->mlx, data->img->img_ptr);
	if(data->img->win)
		mlx_destroy_window(data->img->mlx, data->img->win);
	if(data->img->mlx)
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
	exit(0);
	return (0);
}


int key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		end(data);
	if (keycode == 65361 )
		data->img->key[130] = 1;
	if(keycode == 65363)
		data->img->key[131] = 1;
	if (keycode <= 127)
		data->img->key[keycode] = 1;
	return (0);
}

int key_release(int keycode, t_data *data)
{
	if (keycode <= 127)
		data->img->key[keycode] = 0;
	if (keycode == 65361 )
		data->img->key[130] = 0;
	if(keycode == 65363)
		data->img->key[131] = 0;
	return (0);
}



void move_front(t_data *data)
{
	if (data->img->key['w'])
	{
		double next_x = data->img->player_x + cos(data->img->player_angle) * PLAYER_SPEED;
		double next_y = data->img->player_y + sin(data->img->player_angle) * PLAYER_SPEED;

		if (data->content[(int)(next_y)][(int)(next_x)] != '1')
		{
			data->img->player_x = next_x;
			data->img->player_y = next_y;
		}
	}
}

void move_back(t_data *data)
{
	if (data->img->key['s'])
	{
	
		double next_x = data->img->player_x - cos(data->img->player_angle) * PLAYER_SPEED;
		double next_y = data->img->player_y - sin(data->img->player_angle) * PLAYER_SPEED;
		if (data->content[(int)(next_y)][(int)(next_x)] != '1')
		{
			
			data->img->player_x = next_x;
			data->img->player_y = next_y;
		}
	}
}



void move_right(t_data *data)
{
	if (data->img->key['d'])
	{
		double next_x = data->img->player_x + cos(data->img->player_angle + PI / 2) * PLAYER_SPEED;
		double next_y = data->img->player_y + sin(data->img->player_angle + PI / 2) * PLAYER_SPEED;
		if (data->content[(int)(next_y)][(int)(next_x)] != '1')
		{
			data->img->player_x = next_x;
			data->img->player_y = next_y;
		}
	}
}
void move_left(t_data *data)
{
	if (data->img->key['a'])
	{

		double next_x = data->img->player_x - cos(data->img->player_angle + PI / 2) * PLAYER_SPEED;
		double next_y = data->img->player_y - sin(data->img->player_angle + PI / 2) * PLAYER_SPEED;

		if (data->content[(int)(next_y)][(int)(next_x)] != '1')
		{

			data->img->player_x = next_x;
			data->img->player_y = next_y;
		}
	}
}
int get_color(int r, int g, int b)
{
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

int move_player(t_data *data)
{

	data->img->ceiling_color = get_color(data->ceiling_r, data->ceiling_g, data->ceiling_b);
	data->img->floor_color= get_color(data->floor_r, data->floor_g, data->floor_b);
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
	data->img->addr = mlx_get_data_addr(data->img->img_ptr, &data->img->bpp, &data->img->size_line, &data->img->endian);
	draw(data, data->img); 
	mlx_put_image_to_window(data->img->mlx, data->img->win, data->img->img_ptr, 0, 0);
	return (1);      
}



void find_player_position(t_data *data)
{
	int i = 0;
	while (data->content[i])
	{
		int j = 0;
		while (data->content[i][j])
		{
			if (data->content[i][j] != '1' && data->content[i][j] != '0')
			{
				data->img->player_x = j;
				data->img->player_y = i;
				data->img->facing = data->content[i][j];	
				data->content[i][j] = '0';
				return;
			}
			j++;
		}
		i++;
	}
}

void texture_loading(t_data *data)
{
	char *paths[4] = { data->no, data->so, data->ea, data->we };
	int i;
	
	i = 0;
	while(i < 4)
	{
		data->wall_textures[i].img_ptr = mlx_xpm_file_to_image(data->img->mlx, paths[i],
			&data->wall_textures[i].width, &data->wall_textures[i].height);
		if (!data->wall_textures[i].img_ptr)
		{
			ft_putstr_fd("Error: Failed to load texture: ", 2);
			ft_putendl_fd(paths[i], 2);
			free_textures(data->img->mlx, data->wall_textures, i);
			free_all(data);
			exit(EXIT_FAILURE);
		}
		data->wall_textures[i].addr = mlx_get_data_addr(data->wall_textures[i].img_ptr, &data->wall_textures[i].bpp,
			&data->wall_textures[i].size_line, &data->wall_textures[i].endian);
		i++;
	}
}


void render(t_data *data)
{
	data->img = malloc(sizeof(t_img));	
	data->img->key = malloc(sizeof(char) * 150);
	data->img->player_angle =0.0;
	data->img->ray_distances = malloc(sizeof(double) * WIDTH);
	data->img->ray_angles = malloc(sizeof(double) * WIDTH);
	data->img->wall_directions = malloc(sizeof(char) * WIDTH);
	data->wall_textures = malloc(sizeof(t_img) * 4);
	ft_memset(data->img->key, 0, 150);
	ft_memset(data->img->ray_distances, 0, WIDTH);
	ft_memset(data->img->ray_angles, 0, WIDTH);
    data->img->mlx = mlx_init();
	data->img->win = mlx_new_window(data->img->mlx, WIDTH, HEIGHT, "Pinky & Brain");
	data->img->img_ptr = mlx_new_image(data->img->mlx, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img_ptr, &data->img->bpp, &data->img->size_line, &data->img->endian);
	texture_loading(data);
    find_player_position(data);
	mlx_hook(data->img->win, 17, 0, end, data);
	mlx_hook(data->img->win, 02, (1L << 0), key_press, data);
	mlx_hook(data->img->win, 03, (1L << 1), key_release, data);
	mlx_loop_hook(data->img->mlx, move_player, data);
	mlx_put_image_to_window(data->img->mlx, data->img->win, data->img->img_ptr, 0, 0);
	mlx_loop(data->img->mlx);

}


