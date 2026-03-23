/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:08:36 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/01 18:54:15 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *) s;
	while (n > 0)
	{
		*tmp = (unsigned char) c;
		tmp++;
		n--;
	}
	return (s);
}
