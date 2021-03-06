/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flegg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 00:30:51 by flegg             #+#    #+#             */
/*   Updated: 2020/11/18 17:58:55 by flegg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	ln;

	ln = n;
	if (ln < 0)
	{
		c = '-';
		write(fd, &c, 1);
		ln = -ln;
	}
	if (ln < 10)
	{
		c = '0' + ln;
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd((int)(ln / 10), fd);
		c = '0' + ln % 10;
		write(fd, &c, 1);
	}
	return ;
}
