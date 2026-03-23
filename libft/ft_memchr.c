/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:58:36 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/14 22:31:37 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		ch;

	ptr = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*ptr == ch)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
/*int	main(void)
{
	char str[] = {'a', 'b', '\0', 'c', 'd'};

	printf("Cas 1 : cherche a -> %s\n", (char *)ft_memchr(str, 'a', 5));
	printf("Cas 2 : cherche c -> %s\n", (char *)ft_memchr(str, 'c', 5));
	printf("Cas 3 : cherche '\\0' -> %s\n", (char *)ft_memchr(str, '\0', 5));
	printf("Cas 4 : cherche z -> %s\n", (char *)ft_memchr(str, 'z', 5));
	printf("Cas 5 : cherche c dans 2 premiers octets -> %s\n",
		(char *)ft_memchr(str, 'c', 2));

	return (0);
}*/
