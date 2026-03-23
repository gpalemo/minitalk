/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:42:05 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/20 19:49:34 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
/*int	main()
{
	t_list	*a = ft_lstnew("dame");
	t_list	*b = ft_lstnew("un");
	t_list	*c = ft_lstnew("grrr");

	a->next = b;
	b->next = c;

	t_list	*last = ft_lstlast(a);
	if (last)
		printf("content of the last node : %s\n", (char *)last->content);
	free(a);
	free(b);
	free(c);

	return (0);
}*/
