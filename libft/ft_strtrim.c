/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:19:26 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/15 22:25:05 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*s3;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && inset(s1[i], set))
		i++;
	j = ft_strlen(s1);
	while (j > i && inset(s1[j - 1], set))
		j--;
	len = j - i;
	s3 = (char *)malloc(len + 1);
	if (!s3)
		return (NULL);
	ft_memcpy(s3, s1 + i, len);
	s3[len] = '\0';
	return (s3);
}
