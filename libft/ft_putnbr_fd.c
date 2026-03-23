/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 23:37:46 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/14 23:00:11 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;

	ln = n;
	if (ln < 0)
	{
		ft_putchar_fd('-', fd);
		ln *= -1;
	}
	if (ln <= 9)
		ft_putchar_fd(ln + '0', fd);
	else
	{
		ft_putnbr_fd(ln / 10, fd);
		ft_putnbr_fd(ln % 10, fd);
	}
}
