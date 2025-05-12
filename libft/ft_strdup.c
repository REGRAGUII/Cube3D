/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:28:31 by rboulaga          #+#    #+#             */
/*   Updated: 2025/05/12 06:33:04 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*string;

	if (!s)
		return (0);
	len = ft_strlen(s);
	i = 0;
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
