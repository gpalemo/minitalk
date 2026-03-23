/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:54:33 by cmauley           #+#    #+#             */
/*   Updated: 2026/02/23 23:24:02 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putptr(void *ptr)
{
	int	res;
	int	count;

	if (ptr == NULL)
	{
		res = ft_putstr("(nil)");
		if (res == -1)
			return (-1);
		return (res);
	}
	count = 0;
	res = ft_putstr("0x");
	if (res == -1)
		return (-1);
	count += res;
	res = ft_puthex((unsigned long)ptr, 0);
	if (res == -1)
		return (-1);
	count += res;
	return (count);
}
