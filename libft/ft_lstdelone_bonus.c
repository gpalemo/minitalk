/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:41:02 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/17 19:11:13 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

/*void del_content(void *content)
{
    free(content);
}

int main ()
{
	char *str = ft_strdup("cacaboudin");
	t_list *elem = ft_lstnew(str);
	printf("avant %s\n", (char *)elem->content);
	ft_lstdelone(elem, del_content);
	printf("apres %s\n", (char *)elem->content);
}*/
