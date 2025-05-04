/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:51:37 by rabia             #+#    #+#             */
/*   Updated: 2025/04/28 18:50:50 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



void	verify_map_elements(t_data *data, t_map *map)
{
	preparing_elements(data, map);
	check_access(data, map);
	check_f_rgb(data, map);
	check_c_rgb(data, map);
	
}

void	take_elements(t_data *data, t_map *map)
{
	while(map->next)
	{
		if (map->type == NO)
			data->no = map->line;
		else if (map->type == EA)
			data->ea = map->line;
		else if (map->type == SO)
			data->so = map->line;
		else if (map->type == WE)
			data->we = map->line;
		else if (map->type == F)
			data->f = map->line;
		else if (map->type == C)
			data->c = map->line;
		map = map->next;
	}
}

void	take_it(t_data *data, t_map *map)
{
	int i;

	i = 0;
	while(map->next)
	{
		data->content[i++] = map->line;
		map = map->next;
	}
	data->content[i] = NULL;
}
void    Invalid_element(t_data *data, t_map *map, t_map *tmp)
{
	while(map->next && map->type == MAPP)
	{
		data->map_y++;
		map = map->next;
	}
	if (map->next == NULL)
		return ;
	if(map->type == EMPTY)
	{
		while(map->next && map->type == EMPTY )
			map = map->next;
		if (map->next == NULL)
			return ;
	}
	free_map(tmp);
	my_exit(data, "Invalid element in configuration file\n");
}

void    take_map(t_data *data, t_map *map)
{
	t_map *tmp;// to save the first pointer of map

	tmp = map;
	while(map->next && map->type != MAPP)
		map = map->next;
	Invalid_element(data, map, tmp);
	data->content = malloc(sizeof(char *) * data->len);
	take_it(data, map);
	take_elements(data, tmp);
	verify_map_elements(data, tmp);
	// //you should check if the there is empty line inside of mapp or some wrong characters
}

//
// if (map->type != MAPP && map->type != EMPTY)
// {
//     free(map);
//     my_exit(data, "Invalid element in configuration file\n");
// }
// if (map->type == EMPTY)
// {
//     while(map->type == EMPTY && map->next)

// }
