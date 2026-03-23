/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:13:04 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/07 22:05:30 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (s == 0)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len >= s_len)
		len = s_len - start;
	sub = (char *)malloc(len + 1);
	if (sub == 0)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
/*int	main()
{
	char	*s = "bonjour";
	char	*sub;

	sub = ft_substr(s, 2, 3);
	printf("%s\n", sub);
	free(sub);
	return (0);
}*/
