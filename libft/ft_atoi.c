/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:43:04 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/06 23:12:30 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign = sign * -1;
		}
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}
/*int main(int ac,char **av)
{
	if (ac != 2)
		return(1);
	long result = ft_atoi(av[1]);
	printf("%ld\n",result);
}*/
