/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:05:14 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/15 17:34:23 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned char		*s;

	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (d == s || n == 0)
		return (dest);
	if (s < d)
	{
		while (n)
		{
			n--;
			d[n] = s[n];
		}
	}
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
