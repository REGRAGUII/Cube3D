/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:28:46 by rboulaga          #+#    #+#             */
/*   Updated: 2025/04/28 18:50:50 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

long long	rgb_atoi(const char *str)
{
	int	i;
	long long	res;

	i = 0;
	res = 0;
	if (!str)
		return -1;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = (res * 10) + (str[i] - 48);
		else
			return -1;
		i++;
	}
	if (res < 0 || res > 255)
		return (-1);
	return (res);
}

void remove_newline(char *str)
{
	int i;


	i = 0;
	if (!str)
		return;

	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			return;
		}
		i++;
	}
}

t_map	*map_lstlast(t_map *lst)
{
	if (!lst)
		return (NULL);
	while ( lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	map_add_front(t_map **lst, t_map *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	map_add_back(t_map **lst, t_map *new)
{
	t_map	*head;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		head = map_lstlast(*lst);
		head->next = new;
	}
}
