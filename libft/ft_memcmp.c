/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 02:29:06 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/06 21:11:43 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (n--)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
	}
	return (0);
}
/*int main()
{
    char s1[] = "abcde";
    char s2[] = "abcXe";
    char s3[] = "abcde";

    printf("s1 vs s2 (diff à la 4e lettre) : %d\n", ft_memcmp(s1, s2, 5));
    printf("s1 vs s3 (les mêmes) : %d\n", ft_memcmp(s1, s3, 5));

    return (0);
}*/
