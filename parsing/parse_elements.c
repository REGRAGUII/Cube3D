/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:36:44 by rboulaga          #+#    #+#             */
/*   Updated: 2025/05/12 06:21:24 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_map(t_map *map)
{
	t_map	*temp;

	while (map)
	{
		temp = map->next;
		free(map->line);
		free(map);
		map = temp;
	}
}

void	check_arranging(t_data *data, t_map *map)
{
	int		i;
	t_map	*tmp;

	tmp = map;
	i = 0;
	while (map->next && map->type != MAPP)
	{
		if (map->type == NO || map->type == SO || map->type == WE
			|| map->type == EA || map->type == F || map->type == C)
			i++;
		else if (map->type == NOTHING)
		{
			free_map(tmp);
			my_exit(data, "Invalid element in configuration file\n");
		}
		map = map->next;
	}
	if (i != 6)
	{
		free_map(tmp);
		my_exit(data, "Map content must be the last element in the file\n");
	}
}

void	check_it(t_map *map, t_data *data)
{
	if (data->flag_no != 1 || data->flag_so != 1 || data->flag_we != 1
		|| data->flag_ea != 1 || data->flag_c != 1 || data->flag_f != 1
		|| data->flag_mapp != 1)
	{
		free_map(map);
		my_exit(data, "Invalid map elements: missing or duplicated entries\n");
	}
}

void	check_number_of_elements(t_map *map, t_data *data)
{
	while (map->next)
	{
		if (map->type == 0)
			data->flag_no += 1;
		else if (map->type == 1)
			data->flag_so += 1;
		else if (map->type == 2)
			data->flag_we += 1;
		else if (map->type == 3)
			data->flag_ea += 1;
		else if (map->type == 4)
			data->flag_f += 1;
		else if (map->type == 5)
			data->flag_c += 1;
		else if (map->type == 6)
			data->flag_mapp = 1;
		else
			data->flag_empty = 1;
		map = map->next;
	}
}
