/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:51:37 by rabia             #+#    #+#             */
/*   Updated: 2025/05/12 06:43:27 by rboulaga         ###   ########.fr       */
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
	while (map->next)
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

void	right_wall(char *s, t_data *data, t_map *map)
{
	int	i;

	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	if (!s[i])
		return ;
	else if (s[i] == '0')
	{
		free_map(map);
		my_exit(data, "Invalid element or enclosed wall\n");
	}
}

void	invalid_element(t_data *data, t_map *map, t_map *tmp)
{
	while (map->next && map->type == MAPP)
	{
		data->map_y++;
		map = map->next;
	}
	if (map->next == NULL)
		return ;
	if (map->type == EMPTY)
	{
		while (map->next && map->type == EMPTY)
			map = map->next;
		if (map->next == NULL)
			return ;
	}
	right_wall(map->line, data, tmp);
	free_map(tmp);
	my_exit(data, "Invalid element in configuration file\n");
}

void	take_map(t_data *data, t_map *map)
{
	t_map	*tmp;

	tmp = map;
	while (map->next && map->type != MAPP)
		map = map->next;
	invalid_element(data, map, tmp);
	data->content = malloc(sizeof(char *) * data->len);
	take_it(data, map);
	take_elements(data, tmp);
	verify_map_elements(data, tmp);
}
