/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:56:43 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/06 21:30:21 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	i = 0;
	len_dst = 0;
	len_src = 0;
	while (dst[len_dst] && len_dst < dstsize)
		len_dst++;
	while (src[len_src])
		len_src++;
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	while (src[i] && (len_dst + i) < (dstsize - 1))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
/*int main()
{
    char dest[16] = "classic";
    size_t ret = ft_strlcat(dest, " burger", sizeof(dest));

    printf("dest = \"%s\"\n", dest);
    printf("ret = %zu\n", ret);
}*/
