/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:42:50 by rboulaga          #+#    #+#             */
/*   Updated: 2023/12/06 23:14:38 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bs;
	unsigned char	ps;
	size_t			i;

	bs = (unsigned char *)b;
	ps = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		bs[i] = ps;
		i++;
	}
	return (bs);
}
