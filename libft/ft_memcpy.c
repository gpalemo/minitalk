/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:33:00 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/06 23:37:03 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	int				i;

	i = 0;
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (!src && !dest)
		return (dest);
	while (n)
	{
		d[i] = s[i];
		i++;
		n--;
	}
	return (dest);
}
