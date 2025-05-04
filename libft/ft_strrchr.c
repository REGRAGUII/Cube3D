/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:28:22 by rboulaga          #+#    #+#             */
/*   Updated: 2023/12/06 23:11:23 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	size_t	index;

	result = NULL;
	index = 0;
	while (s[index])
	{
		if (s[index] == (char)c)
			result = (char *)&s[index];
		index++;
	}
	if ((char)c == '\0')
		result = (char *)&s[index];
	return (result);
}
