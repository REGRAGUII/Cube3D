/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yregragu <yregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:19:12 by yregragu          #+#    #+#             */
/*   Updated: 2025/05/12 22:09:18 by yregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	get_map_width(char *row)
{
	int	i;

	i = 0;
	while (row[i])
		i++;
	return (i);
}

int	get_color(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	player_facing(t_img *img)
{
	char	f;

	f = img->facing;
	if (img->facing == 'N')
		img->player_angle = 3 * PI / 2;
	if (img->facing == 'E')
		img->player_angle = 0.0;
	if (img->facing == 'S')
		img->player_angle = PI / 2;
	if (img->facing == 'W')
		img->player_angle = PI;
}

void	find_player_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->content[i])
	{
		j = 0;
		while (data->content[i][j])
		{
			if (data->content[i][j] != '1' && data->content[i][j] != '0')
			{
				data->img->player_x = j;
				data->img->player_y = i;
				data->img->facing = data->content[i][j];
				data->content[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
