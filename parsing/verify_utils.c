/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:55:20 by rboulaga          #+#    #+#             */
/*   Updated: 2025/04/28 18:50:50 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb_help(char *str)
{
	int i;
	int j;

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

void	check_c_rgb(t_data *data, t_map *map)
{
	char **colors_c;

	colors_c = ft_split(data->c, ',');
	if (!colors_c[0] || !colors_c[1] || !colors_c[2])
	{
		free(colors_c);
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid RGB color format\n");
	}
	data->ceiling_r = rgb_atoi(colors_c[0]);
	data->ceiling_g = rgb_atoi(colors_c[1]);
	data->ceiling_b = rgb_atoi(colors_c[2]);
	free_list(colors_c);
	if (data->ceiling_r == -1 || data->ceiling_g == -1
		|| data->ceiling_b == -1)
	{
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid RGB color format\n");
	}
}

void	check_f_rgb(t_data *data, t_map *map)
{
	char **colors_f;

	colors_f = ft_split(data->f, ',');
	if (!colors_f[0] || !colors_f[1] || !colors_f[2])
	{
		free(colors_f);
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid RGB color format\n");
	}
	data->floor_r = rgb_atoi(colors_f[0]);
	data->floor_g = rgb_atoi(colors_f[1]);
	data->floor_b = rgb_atoi(colors_f[2]);
	free_list(colors_f);
	if (data->floor_r == -1 || data->floor_g == -1
		|| data->floor_b == -1)
	{
		free_map(map);
		free(data->content);
		my_exit(data, "Invalid RGB color format\n");
	}
}

void	check_access(t_data *data, t_map *map)
{
	int i;

	i = 0;
	if (access(data->ea, F_OK) != 0
		|| access(data->we, F_OK) != 0
		|| access(data->so, F_OK) != 0
		|| access(data->no, F_OK) != 0
		|| access(data->no, R_OK) != 0
		|| access(data->so, R_OK) != 0
		|| access(data->we, R_OK) != 0
		|| access(data->ea, R_OK) != 0)
	{
		free_map(map);
		free(data->content);
		my_exit(data, "File does not exist or permission denied\n");
	}
	while (data->content[i])
	{
		remove_newline(data->content[i]);
		i++;
	}
}


char	*helper(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	while(str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	str = &str[i];
	return (str);
}

void	preparing_elements(t_data *data, t_map *map)
{
	int i;

	i = 0;
	data->no = helper(data->no);
	data->so = helper(data->so);
	data->ea = helper(data->ea);
	data->we = helper(data->we);
	data->f = helper(data->f);
	data->c = helper(data->c);
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
