/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:27:44 by cmauley           #+#    #+#             */
/*   Updated: 2026/02/23 23:23:38 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;
	int	res;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
	{
		res = write(1, &str[i], 1);
		if (res == -1)
			return (-1);
		i++;
	}
	return (i);
}
