/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:32:53 by rboulaga          #+#    #+#             */
/*   Updated: 2023/12/03 10:52:10 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <fcntl.h>

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = (long)n;
	if (fd < 0)
		return ;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	if (num <= 9)
	{
		num += '0';
		ft_putchar_fd(num, fd);
	}
	else
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
}

// int main ()
// {
//     int n;

//     n = -0;
//     int fd = open ("test.txt", O_RDWR);
//     ft_putnbr_fd (n, fd);
// }