/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:38:48 by rboulaga          #+#    #+#             */
/*   Updated: 2025/02/17 14:38:48 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int main(int ac, char **av)
{
	t_data	*data;
	t_map	*map;

	data = malloc(sizeof(t_data));
	map = malloc(sizeof(t_map));
	
	ft_memset(data, 0, sizeof(t_data));
	ft_memset(map, 0, sizeof(t_map));
	parsing(ac, av, data, map);
	render(data);
	return (0);
}


