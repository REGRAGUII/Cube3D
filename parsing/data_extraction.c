/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_extraction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:19:45 by rboulaga          #+#    #+#             */
/*   Updated: 2025/05/12 06:16:18 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	my_cmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (*s2 && (*s2 == ' ' || *s2 == '	'))
		s2++;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

void	type_definition(t_map *map)
{
	while (map->next)
	{
		if (!my_cmp("NO", map->line, 2))
			map->type = NO;
		else if (!my_cmp("SO", map->line, 2))
			map->type = SO;
		else if (!my_cmp("WE", map->line, 2))
			map->type = WE;
		else if (!my_cmp("EA", map->line, 2))
			map->type = EA;
		else if (!my_cmp("F", map->line, 1))
			map->type = F;
		else if (!my_cmp("C", map->line, 1))
			map->type = C;
		else if (!my_cmp("1", map->line, 1))
			map->type = MAPP;
		else if (!my_cmp("\n", map->line, 1))
			map->type = EMPTY;
		else
			map->type = NOTHING;
		map = map->next;
	}
}

void	get_elements(t_map *map, char *str)
{
	t_map	*newnode;

	newnode = (t_map *)malloc(sizeof(t_map));
	newnode->line = ft_strdup(str);
	newnode->flag = 0;
	newnode->next = NULL;
	if (!map)
		map_add_front(&map, newnode);
	map_add_back(&map, newnode);
	(void)str;
}

void	delete_spaces(t_map *map)
{
	t_map	*tmp;
	char	*str;

	tmp = map;
	while (tmp->next)
	{
		if (tmp->type != MAPP)
		{
			str = ft_strtrim(tmp->line, " \t\n\v\r\f");
			free(tmp->line);
			tmp->line = str;
		}
		tmp = tmp->next;
	}
}

void	data_extraction(char *file, t_data *data, t_map *map)
{
	char	*str;

	data->fd = open(file, O_RDONLY);
	map->line = get_next_line(data->fd);
	str = map->line;
	while (str)
	{
		str = get_next_line(data->fd);
		get_elements(map, str);
		free(str);
	}
	close(data->fd);
	type_definition(map);
	delete_spaces(map);
	check_number_of_elements(map, data);
	check_it(map, data);
	check_arranging(data, map);
}
