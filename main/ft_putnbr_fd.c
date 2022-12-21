/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:14:32 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/18 15:02:28 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	long long int	internal_n;

	internal_n = (long long int)n;
	if (internal_n < 0)
	{
		write(fd, "-", 1);
		internal_n = -internal_n;
	}
	c = internal_n % 10 + '0';
	if (internal_n / 10)
	{
		ft_putnbr_fd(internal_n / 10, fd);
		write(fd, &c, 1);
	}
	else
		write(fd, &c, 1);
}
