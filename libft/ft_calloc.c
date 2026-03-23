/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:28:06 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/08 19:20:19 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			total;

	tmp = 0;
	total = count * size;
	tmp = malloc(total);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, total);
	return (tmp);
}
/*int	main()
{
	int *tab;
	int i;

	tab = ft_calloc(5, sizeof(int));
	if (!tab)
		return(1);
	i = 0;
	while (i < 5)
	{
		printf("%d\n", tab[i]);
		i++;
	}
	free(tab);
	return (0);
}*/
