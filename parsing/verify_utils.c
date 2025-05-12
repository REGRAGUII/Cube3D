/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:55:20 by rboulaga          #+#    #+#             */
/*   Updated: 2025/05/12 06:27:40 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_c_rgb(t_data *data, t_map *map)
{
	char	**colors_c;

	colors_c = ft_split(data->c, ',');
	if (!colors_c[0] || !colors_c[1] || !colors_c[2])
	{
		free_list(colors_c);
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid RGB color format\n");
	}
	data->ceiling_r = rgb_atoi(colors_c[0]);
	data->ceiling_g = rgb_atoi(colors_c[1]);
	data->ceiling_b = rgb_atoi(colors_c[2]);
	free_list(colors_c);
	if (data->ceiling_r == -1 || data->ceiling_g == -1 || data->ceiling_b == -1)
	{
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid RGB color format\n");
	}
}

void	check_f_rgb(t_data *data, t_map *map)
{
	char	**colors_f;

	colors_f = ft_split(data->f, ',');
	if (!colors_f[0] || !colors_f[1] || !colors_f[2])
	{
		free_list(colors_f);
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid RGB color format\n");
	}
	data->floor_r = rgb_atoi(colors_f[0]);
	data->floor_g = rgb_atoi(colors_f[1]);
	data->floor_b = rgb_atoi(colors_f[2]);
	free_list(colors_f);
	if (data->floor_r == -1 || data->floor_g == -1 || data->floor_b == -1)
	{
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid RGB color format\n");
	}
}

void	textures(char *s, t_data *data, t_map *map)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd == -1)
	{
		free_map(map);
		free(data->content);
		my_exit(data, "Texture file does not exist or permission is denied\n");
	}
	close(fd);
}

void	check_access(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	textures(data->we, data, map);
	textures(data->ea, data, map);
	textures(data->so, data, map);
	textures(data->no, data, map);
	while (data->content[i])
	{
		remove_newline(data->content[i]);
		i++;
	}
}

void	preparing_elements(t_data *data, t_map *map)
{
	data->no = helper(data->no, data, map);
	data->so = helper(data->so, data, map);
	data->ea = helper(data->ea, data, map);
	data->we = helper(data->we, data, map);
	data->f = helper(data->f, data, map);
	data->c = helper(data->c, data, map);
	remove_newline(data->no);
	remove_newline(data->ea);
	remove_newline(data->we);
	remove_newline(data->so);
	remove_newline(data->f);
	remove_newline(data->c);
	if (rgb_help(data->f) != 2 || rgb_help(data->c) != 2)
	{
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid RGB color format\n");
	}
}
