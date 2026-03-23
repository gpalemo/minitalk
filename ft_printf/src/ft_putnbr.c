/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:55:47 by cmauley           #+#    #+#             */
/*   Updated: 2026/02/23 23:23:53 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putnbr(int nbr)
{
	int		count;
	int		res;
	long	ln;

	count = 0;
	ln = nbr;
	if (ln < 0)
	{
		res = ft_putchar('-');
		if (res == -1)
			return (-1);
		count += res;
		ln = -ln;
	}
	if (ln >= 10)
	{
		res = ft_putnbr(ln / 10);
		if (res == -1)
			return (-1);
		count += res;
	}
	res = ft_putchar((ln % 10) + '0');
	if (res == -1)
		return (-1);
	return (count + res);
}
