/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:42:51 by rboulaga          #+#    #+#             */
/*   Updated: 2023/12/06 23:11:23 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *string, unsigned int start, size_t len)
{
	char			*str1;
	unsigned int	j;
	unsigned int	i;

	j = 0;
	i = start;
	if (!string)
		return (NULL);
	if (start >= ft_strlen(string))
		return (ft_strdup(""));
	if (len > ft_strlen(string) - start)
		len = (ft_strlen(string) - start);
	str1 = malloc(sizeof(char) * (len + 1));
	if (!str1)
		return (NULL);
	while (string[i] && i < len + start)
	{
		str1[j] = string[i];
		j++;
		i++;
	}
	str1[j] = '\0';
	return (str1);
}
