/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:46:59 by cmauley           #+#    #+#             */
/*   Updated: 2026/02/23 23:23:28 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putunbr(unsigned int nbr)
{
	int		count;
	int		res;

	count = 0;
	if (nbr >= 10)
	{
		res = ft_putunbr(nbr / 10);
		if (res == -1)
			return (-1);
		count += res;
	}
	res = ft_putchar((nbr % 10) + '0');
	if (res == -1)
		return (-1);
	return (count + res);
}
