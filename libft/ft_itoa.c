/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 22:39:12 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/14 22:29:43 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nblen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/*static int	ncheck(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}*/

char	*ft_itoa(int n)
{
	int		len;
	long	num;
	char	*res;

	num = n;
	len = nblen(n);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (num < 0)
	{
		num = -num;
		res[0] = '-';
	}
	else if (n == 0)
		res[0] = '0';
	while (num > 0)
	{
		res[len] = (num % 10) + 48;
		num /= 10;
		len -= 1;
	}
	return (res);
}
// int	main()
// {
// 	printf("%s\n", ft_itoa(123));
// 	return (0);
// }
