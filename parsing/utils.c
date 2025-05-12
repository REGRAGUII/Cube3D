/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:21:41 by rboulaga          #+#    #+#             */
/*   Updated: 2025/05/12 06:26:39 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb_help(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	return (j);
}

char	*helper(char *str, t_data *data, t_map *map)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	if (is_space(str[i]) == 0)
	{
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid format (texture or RGB)\n");
	}
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	str = &str[i];
	return (str);
}

void	take_it(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	while (map->next)
	{
		data->content[i++] = map->line;
		map = map->next;
	}
	data->content[i] = NULL;
}

void	free_list(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
