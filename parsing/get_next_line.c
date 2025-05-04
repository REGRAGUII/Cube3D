/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:12:25 by rboulaga          #+#    #+#             */
/*   Updated: 2025/04/28 18:50:50 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_new_line(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (-1);
}

char	*rightside(char *reminder)
{
	char	*tmp_again;

	tmp_again = ft_strdupp(ft_strchrr(reminder, '\n'));
	if (!tmp_again)
		return (NULL);
	else if (tmp_again)
	{
		free(reminder);
		reminder = ft_strdupp(tmp_again + 1);
	}
	free(tmp_again);
	return (reminder);
}

char	*leftside(char *reminder)
{
	char	*tmp;
	char	*str;
	int		i;
	char	*save;

	str = NULL;
	i = 0;
	save = ft_strdupp(reminder);
	tmp = ft_strchrr(save, '\n');
	if (!tmp)
		return (free(save), reminder);
	if (tmp)
	{
		while (save[i] != '\n')
			i++;
		save[i + 1] = '\0';
		str = ft_strdupp(save);
	}
	free(save);
	return (str);
}

char	*read_for_me(char *reminder, int fd, char *buff)
{
	int	counter;

	counter = 1;
	while (counter != 0)
	{
		counter = read(fd, buff, BUFFER_SIZE);
		if (counter == 0)
			break ;
		if (counter == -1)
			return (free(buff), free(reminder), NULL);
		buff[counter] = '\0';
		reminder = ft_strjoinn(reminder, buff);
		if (ft_new_line(reminder) == 1)
			break ;
	}
	free(buff);
	return (reminder);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*reminder;
	char		*goal;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	reminder = read_for_me(reminder, fd, buff);
	if (!reminder)
		return (NULL);
	if (!reminder[0])
		return (free(reminder), reminder = NULL, NULL);
	goal = leftside(reminder);
	if (!goal)
		return (NULL);
	reminder = rightside(reminder);
	return (goal);
}

	// if (reminder && reminder[0] == '\0')
	// 	free (reminder);
	// reminder = NULL;
