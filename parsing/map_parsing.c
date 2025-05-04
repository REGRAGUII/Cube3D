/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:55:00 by rboulaga          #+#    #+#             */
/*   Updated: 2025/04/28 18:50:50 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	check_components(t_data *data, char *str)
// {
// 	int i;

// 	i = 0;

// 	while (str[i])
// 	{
// 		if (str[i] == '1')
// 	}
// }

void	components(t_data *data, t_map *map)
{
	int i;
	int j;

	i = 0;
	data->help = 0;
	while(data->content[i])
	{
		j = 0;
		while(data->content[i][j])
		{
			if (!ft_strchr("01NWSE", data->content[i][j]))
			{
				free_map(map);
				free(data->content);
				my_exit(data, "Invalid map: Map contains an invalid character\n");
			}
			if (ft_strchr("NWSE", data->content[i][j]))
				data->help++;
			j++;
		}
		i++;
	}
}
void	first_last_walls(t_data *data, t_map *map)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(data->content[0][i] && (data->content[0][i] == '1'
		|| data->content[0][i] == ' '))
		i++;
	while (data->content[data->map_y - 1][j])
	{
		if (data->content[data->map_y - 1][j] == '1'
			|| data->content[data->map_y - 1][j] == ' ')
			j++;
		else
			break;
	}
	if( data->content[0][i] != '\0' || data->content[data->map_y - 1][j] != '\0')
	{
		free_map(map);
		free(data->content);
		my_exit(data, "sssssssssInvalid map: map must be enclosed by walls\n");
	}
}

void	walls(t_data *data, t_map *map)
{
	int i;

	i = 0;
	while(data->content[i])
	{
		if(ft_strlen(data->content[i]) > 1)
		{
			if(data->content[i][ft_strlen(data->content[i]) - 1] == '0')
			{
				free_map(map);
				free(data->content);
				my_exit(data, "Invalid map: map must be enclosed by walls\n");
			}
		}
			i++;
	}
}

void	map_parsing(t_data *data, t_map *map)
{
	components(data, map);
	if (data->help != 1)
	{
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid map: Invalid player position\n");
	}
	first_last_walls(data, map);
	walls(data, map);
}
