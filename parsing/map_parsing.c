/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:55:00 by rboulaga          #+#    #+#             */
/*   Updated: 2025/05/12 06:19:30 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r'
		|| c == '\f')
		return (1);
	else
		return (0);
}

void	components(t_data *data, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	data->help = 0;
	while (data->content[i])
	{
		j = 0;
		while (data->content[i][j])
		{
			if (!ft_strchr(" \t\n\v\f\r01NWSE", data->content[i][j]))
			{
				free_map(map);
				free(data->content);
				my_exit(data,
					"Invalid map: Map contains an invalid character\n");
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
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (data->content[0][i] && (data->content[0][i] == '1'
			|| is_space(data->content[0][i]) == 1))
		i++;
	while (data->content[data->map_y - 1][j])
	{
		if (data->content[data->map_y - 1][j] == '1'
			|| is_space(data->content[data->map_y - 1][j]))
			j++;
		else
			break ;
	}
	if (data->content[0][i] != '\0' || data->content[data->map_y
		- 1][j] != '\0')
	{
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid map: map must be enclosed by walls\n");
	}
}

void	walls(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	while (data->content[i])
	{
		if (ft_strlen(data->content[i]) > 1)
		{
			if (data->content[i][ft_strlen(data->content[i]) - 1] == '0')
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
		my_exit(data, "Invalid map\n");
	}
	first_last_walls(data, map);
	walls(data, map);
}
