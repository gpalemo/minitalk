/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:06:05 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/08 18:01:27 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	j;
	size_t	i;
	char	*res;

	j = 0;
	i = 0;
	res = (char *) malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!res)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}
/*int	main()
{
	char	*s1 = "hello";
	char	*s2 = " world";
	char	*res;

	res = ft_strjoin(s1, s2);
	printf("Result = %s\n", res);
	free(res);
	return (0);
}*/
