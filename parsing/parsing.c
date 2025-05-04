/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:41:53 by rboulaga          #+#    #+#             */
/*   Updated: 2025/04/29 20:18:01 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>

int file_exists(char *file, t_data *data)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		my_exit(data, "Cannot access the file!\n");
	str = get_next_line(fd);
	i++;
	while (str)
	{
		free(str);
		i++;
		str = get_next_line(fd);
	}
	close(fd);
	return (i);
}

void	my_exit(t_data *data, char *str)
{
	free(data);
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

void	check_extension(char *av, t_data *data)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	i--;
	while (av[i] != '.') // kjsdkjfs>.<cub
		i--;
	if ((!av[i - 1]) || av[i - 1] == '/')
		my_exit(data, "invalid extension\n");
	if (ft_strncmp(&av[i], ".cub", 4) != 0)
		my_exit(data, "invalid extension\n");
}

void parsing(int ac, char **av, t_data *data, t_map *map)
{

	// int j = 0;

	if (ac == 2)
	{
		check_extension(av[1], data);
		data->len = file_exists(av[1], data);
		data_extraction(av[1], data, map);
		take_map(data, map);
		map_parsing(data, map);
		return ;
	}
	free(map);
	my_exit(data, "Invalid number of arguments\n");
}


