/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:12:36 by cmauley           #+#    #+#             */
/*   Updated: 2026/02/23 23:24:13 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_puthex(unsigned long nbr, int upper)
{
	const char	*hex;
	int			count;
	int			tmp;

	if (upper == 1)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	count = 0;
	if (nbr >= 16)
	{
		tmp = ft_puthex(nbr / 16, upper);
		if (tmp == -1)
			return (-1);
		count += tmp;
	}
	tmp = ft_putchar(hex[nbr % 16]);
	if (tmp == -1)
		return (-1);
	count += tmp;
	return (count);
}
