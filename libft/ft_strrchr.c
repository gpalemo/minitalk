/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:09:37 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/07 20:00:58 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*res;

	ch = (char) c;
	res = NULL;
	while (*s)
	{
		if (*s == ch)
			res = ((char *)s);
		s++;
	}
	if (*s == ch)
		res = ((char *)s);
	return (res);
}
/*int main()
{
    char *str = "quoikoubeh";

    printf("Recherche de 'q'  -> %s\n", ft_strrchr(str, 'q'));
    printf("Recherche de 'u'  -> %s\n", ft_strrchr(str, 'u'));
    printf("Recherche de 'h'  -> %s\n", ft_strrchr(str, 'h'));

    return (0);
}*/
