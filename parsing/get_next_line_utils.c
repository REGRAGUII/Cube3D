/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:14:22 by rboulaga          #+#    #+#             */
/*   Updated: 2025/04/28 18:50:50 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdupp(char *s)
{
	size_t	len;
	size_t	i;
	char	*string;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlenn(s);
	string = (char *)malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	while (s[i])
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

size_t	ft_strlenn(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strchrr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoinn(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		j;
	int		lens1;
	int		lens2;

	lens1 = ft_strlenn(s1);
	lens2 = ft_strlenn(s2);
	j = 0;
	newstr = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		newstr[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		newstr[j++] = s2[i++];
	newstr[j] = '\0';
	free(s1);
	return (newstr);
}
