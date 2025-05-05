/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:30:42 by youssef           #+#    #+#             */
/*   Updated: 2025/05/05 20:14:55 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define PLAYER_SPEED 0.05


double	rad(double angle)
{
	return (angle * PI / 180);
}


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



void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		char *dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}



void draw_3d_walls(t_data *data)
{
	int col = 0;

	while (col < WIDTH)
	{
		double dist = data->img->ray_distances[col];
		if (dist <= 0)
			dist = 0.0001;

		int line_height = (int)(HEIGHT / dist);
		int draw_start = -line_height / 2 + HEIGHT / 2;
		int draw_end = line_height / 2 + HEIGHT / 2;

		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

	
		int tex_index;
		if (data->img->wall_directions[col] == 'N') tex_index = 0;
		else if (data->img->wall_directions[col] == 'S') tex_index = 1;
		else if (data->img->wall_directions[col] == 'E') tex_index = 2;
		else tex_index = 3;

		t_img *tex = &data->wall_textures[tex_index];

		// tex_X position in the texture
		double wall_x;
		if (data->img->wall_directions[col] == 'N' || data->img->wall_directions[col] == 'S')
			wall_x = data->img->player_x + data->img->ray_distances[col] * cos(data->img->ray_angles[col]);
		else
			wall_x = data->img->player_y + data->img->ray_distances[col] * sin(data->img->ray_angles[col]);

		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * (double)tex->width);
		if (data->img->wall_directions[col] == 'W' || data->img->wall_directions[col] == 'S')
			tex_x = tex->width - tex_x - 1;

	
		int y = 0;
		while (y < HEIGHT)
		{
			if (y < draw_start)
			{
				my_mlx_pixel_put(data->img, col, y, data->img->ceiling_color);
			}
			else if (y >= draw_start && y <= draw_end)
			{
				int tex_y = ((y - draw_start) * tex->height) / (draw_end - draw_start);
				int tex_pos = tex_y * tex->size_line + tex_x * (tex->bpp / 8);
				int color = *(unsigned int *)(tex->addr + tex_pos);
				my_mlx_pixel_put(data->img, col, y, color);
			}
			else
			{
				my_mlx_pixel_put(data->img, col, y, data->img->floor_color);
			}
			y++;
		}
		col++;
	}
}

void draw_view_ray(t_img *img, char **map)
{
    int map_size = 64;
    int col = 0;
	
	while (col < WIDTH)
    {
        double ray_angle = img->player_angle - (FOV_ANGLE / 2.0) + (FOV_ANGLE * col / WIDTH);
        double ray_dir_x = cos(ray_angle);
        double ray_dir_y = sin(ray_angle);

        int map_x = (int)img->player_x;
        int map_y = (int)img->player_y;

		//  1 3la ray_dirx hiya 1/cosx => cosx = x1-x2 / 
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);

        int step_x;
		 if (ray_dir_x < 0)
			step_x = -1;
		 else
			step_x = 1;
		
        int step_y;
		if(ray_dir_y < 0)
			step_y = -1;
		else
			step_y = 1;
			
		double side_dist_x = step_x;
		if(step_x < 0)
            side_dist_x = (img->player_x - map_x) * delta_dist_x;
		else
			side_dist_x = (map_x + 1.0 - img->player_x) * delta_dist_x;

		double side_dist_y = step_y;
		if(step_y < 0)
			side_dist_y = (img->player_y - map_y) * delta_dist_y;
		else
			side_dist_y = (map_y + 1.0 - img->player_y) * delta_dist_y;
	
			

        int hit = 0;
        int side = 0; // 0: X side, 1: Y side

        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map[map_y][map_x] == '1')
                hit = 1;
        }
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;
		
			
		img->ray_distances[col] = perp_wall_dist * cos(ray_angle - img->player_angle);
        img->ray_angles[col] = ray_angle;


        if (side == 0)
            img->wall_directions[col] = (step_x < 0) ? 'E' : 'W';
        else
            img->wall_directions[col] = (step_y < 0) ? 'S' : 'N';

        // 2D
        double draw_x = img->player_x * map_size + map_size / 4;
        double draw_y = img->player_y * map_size + map_size / 4;
		
		int s = 0;
        while(s < perp_wall_dist * map_size)
        {
            int dx = (int)(draw_x + ray_dir_x * s);
            int dy = (int)(draw_y + ray_dir_y * s);
            int color = 0xFF0000;
            if (side == 0)
                color = (step_x < 0) ? 0x00FF00 : 0x0000FF; 
            else
                color = (step_y < 0) ? 0xFFFF00 : 0xFF00FF; 

            my_mlx_pixel_put(img, dx, dy, color);
			s++;
        }
		col++;
	}
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





void player(t_img *img, char **map)
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

	img->wall_directions = malloc(sizeof(char) * WIDTH);
	
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
	// player(img, data->content);
	draw_view_ray(img, data->content);
	
	draw_3d_walls(data);
	
}


int	end(t_img *img)
{
	mlx_destroy_image(img->mlx, img->img_ptr);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->key);
	free(img->mlx);
	free(img);
	exit(0);
	return (0);
}

int key_press(int keycode, t_img *img)
{
	if (keycode == 65307)
		end(img);
	if (keycode == 65361 || keycode == 65363)
		img->key[keycode] = 1;
	if (keycode <= 127)
		img->key[keycode] = 1;
	return (0);
}

int key_release(int keycode, t_img *img)
{
	if (keycode <= 127)
		img->key[keycode] = 0;
	if (keycode == 65361 || keycode == 65363)
		img->key[keycode] = 0;
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
	if (data->img->key[65361])
		data->img->player_angle -= 0.05;
	if (data->img->key[65363])
		data->img->player_angle += 0.05;
	
		
	// printf("angle : %f\n", data->img->player_angle);
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
		data->wall_textures[i].img_ptr = mlx_xpm_file_to_image(data->img->mlx, paths[i], &data->wall_textures[i].width, &data->wall_textures[i].height);
		data->wall_textures[i].addr = mlx_get_data_addr(data->wall_textures[i].img_ptr, &data->wall_textures[i].bpp, &data->wall_textures[i].size_line, &data->wall_textures[i].endian);
		i++;
	}
}


void render(t_data *data)
{
	data->img = malloc(sizeof(t_img));	
	data->img->key = malloc(sizeof(char) * 70000);
	data->img->player_angle =0.0;
	data->img->ray_distances = malloc(sizeof(double) * WIDTH);
	data->img->ray_angles = malloc(sizeof(double) * WIDTH);
	data->wall_textures = malloc(sizeof(t_img) * 4);

	ft_memset(data->img->key, 0, 70000);
	ft_memset(data->img->ray_distances, 0, WIDTH);
	ft_memset(data->img->ray_angles, 0, WIDTH);


    data->img->mlx = mlx_init();
	data->img->win = mlx_new_window(data->img->mlx, WIDTH, HEIGHT, "Pinky & Brain");
	data->img->img_ptr = mlx_new_image(data->img->mlx, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img_ptr, &data->img->bpp, &data->img->size_line, &data->img->endian);
	texture_loading(data);
    find_player_position(data);
	mlx_hook(data->img->win, 17, 0, end, data->img);
	mlx_hook(data->img->win, 02, (1L << 0), key_press, data->img);
	mlx_hook(data->img->win, 03, (1L << 1), key_release, data->img);
	mlx_loop_hook(data->img->mlx, move_player, data);
	mlx_put_image_to_window(data->img->mlx, data->img->win, data->img->img_ptr, 0, 0);
	mlx_loop(data->img->mlx);
}


