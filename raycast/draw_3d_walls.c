/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:04:07 by youssef           #+#    #+#             */
/*   Updated: 2025/05/12 21:51:06 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static int	get_tex_index(char dir)
{
	if (dir == 'N')
		return (0);
	else if (dir == 'S')
		return (1);
	else if (dir == 'E')
		return (2);
	return (3);
}

static void	get_tex_coords(t_data *data, int col, int *tex_x, t_img *tex)
{
	double	coord_x;

	if (data->img->wall_directions[col] == 'N'
		|| data->img->wall_directions[col] == 'S')
		coord_x = data->img->hit_x[col] - floor(data->img->hit_x[col]);
	else
		coord_x = data->img->hit_y[col] - floor(data->img->hit_y[col]);
	*tex_x = (int)(coord_x * (double)tex->width);
	if (data->img->wall_directions[col] == 'W'
		|| data->img->wall_directions[col] == 'S')
		*tex_x = tex->width - *tex_x - 1;
	*tex_x = fmin(fmax(0, *tex_x), tex->width - 1);
}

static void	draw_wall_strip(t_data *data, int col, int start, int end)
{
	t_coord	vect;
	t_img	*tex;
	int		y;
	int		tex_pos;
	int		color;

	tex = &data->wall_textures[get_tex_index(data->img->wall_directions[col])];
	get_tex_coords(data, col, &vect.tex_x, tex);
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < start)
			my_mlx_pixel_put(data->img, col, y, data->img->ceiling_color);
		else if (y >= start && y <= end)
		{
			vect.tex_y = ((y - start) * tex->height) / (end - start);
			tex_pos = vect.tex_y * tex->size_line + vect.tex_x * (tex->bpp / 8);
			color = *(unsigned int *)(tex->addr + tex_pos);
			my_mlx_pixel_put(data->img, col, y, color);
		}
		else
			my_mlx_pixel_put(data->img, col, y, data->img->floor_color);
	}
}

void	draw_3d_walls(t_data *data)
{
	int		col;
	int		line_height;
	int		start;
	int		end;
	double	dist;

	col = -1;
	while (++col < WIDTH)
	{
		dist = data->img->ray_distances[col];
		if (dist <= 0)
			dist = 0.0001;
		line_height = (int)(HEIGHT / dist);
		start = -line_height / 2 + HEIGHT / 2;
		end = line_height / 2 + HEIGHT / 2;
		draw_wall_strip(data, col, start, end);
	}
}
