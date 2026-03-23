/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:39:30 by cmauley           #+#    #+#             */
/*   Updated: 2026/02/23 23:24:26 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	forlow(unsigned int n)
{
	return (ft_puthex((unsigned long)n, 0));
}

static int	forup(unsigned int n)
{
	return (ft_puthex((unsigned long)n, 1));
}

static int	specify_format(char type, va_list *args)
{
	if (type == 'c')
		return (ft_putchar((char)va_arg(*args, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (type == 'u')
		return (ft_putunbr(va_arg(*args, unsigned int)));
	else if (type == 'p')
		return (ft_putptr(va_arg(*args, void *)));
	else if (type == 'x')
		return (forlow(va_arg(*args, unsigned int)));
	else if (type == 'X')
		return (forup(va_arg(*args, unsigned int)));
	else if (type == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		res;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			res = specify_format(str[i + 1], &args);
			i += 2;
		}
		else
			res = ft_putchar(str[i++]);
		if (res == -1)
			break ;
		count += res;
	}
	va_end(args);
	if (res == -1)
		return (-1);
	return (count);
}
