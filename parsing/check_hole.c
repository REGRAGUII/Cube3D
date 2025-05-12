/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hole.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:43:49 by rboulaga          #+#    #+#             */
/*   Updated: 2025/05/12 06:15:20 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	else
		return (0);
}

void	hole_error(t_data *data, t_map *map)
{
	free_map(map);
	free(data->content);
	my_exit(data, "Invalid map\n");
}

int	valide_line(t_data *data, int i, int j)
{
	int	len;

	len = ft_strlen(data->content[i]);
	if (len > j)
	{
		if (is_space(data->content[i][j]) == 1)
			return (0);
	}
	else if (len <= j)
		return (0);
	return (1);
}

void	searx(int i, int j, t_data *data, t_map *map)
{
	if (is_space(data->content[i][j + 1]))
		hole_error(data, map);
	else if (is_space(data->content[i][j - 1]))
		hole_error(data, map);
	else if (valide_line(data, i + 1, j) == 0)
		hole_error(data, map);
	else if (valide_line(data, i - 1, j) == 0)
		hole_error(data, map);
}

void	check_hole(t_data *data, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (data->content[i])
	{
		j = 0;
		while (data->content[i][j])
		{
			if (data->content[i][j] == '0')
				searx(i, j, data, map);
			else if (check_player(data->content[i][j]))
				searx(i, j, data, map);
			j++;
		}
		i++;
	}
}
