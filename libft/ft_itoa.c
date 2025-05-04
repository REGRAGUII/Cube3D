/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:46:20 by rboulaga          #+#    #+#             */
/*   Updated: 2023/12/06 23:14:49 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_calcul(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_is_negative(long n, int len)
{
	char	*str;

	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[0] = '-';
	str[len] = '\0';
	n = n * -1;
	while (--len > 0 && n > 0)
	{
		str[len] = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		len;

	len = ft_calcul(n);
	if (n < 0)
		return (ft_is_negative(n, len));
	string = malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	string[len] = '\0';
	len--;
	while (len >= 0)
	{
		string[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (string);
}
