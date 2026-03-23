/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:32:50 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/17 19:11:23 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}

/*static void	functiontest(void *str)
{
	char *temp = (char *)str;

	temp[0] = 'd';
	return ;
}

int main ()
{
	char *str1 = ft_strdup("hello");
    char *str2 = ft_strdup("world");
    char *str3 = ft_strdup("hugo");
	t_list	*elem = ft_lstnew(str1);
	t_list	*elem2 = ft_lstnew(str2);
	t_list	*elem3 = ft_lstnew(str3);

	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = NULL;

	ft_lstiter(elem, functiontest);
	printf("elem = %s\n", (char *)elem->content);
	printf("elem2 = %s\n", (char *)elem2->content);
	printf("elem3 = %s\n", (char *)elem3->content);
}*/
