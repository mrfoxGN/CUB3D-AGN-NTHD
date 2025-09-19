/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:40:14 by ntahadou          #+#    #+#             */
/*   Updated: 2024/11/09 11:50:26 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*node;
	void	*newcontent;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	result = NULL;
	while (lst)
	{
		newcontent = f(lst->content);
		node = ft_lstnew(newcontent);
		if (node == NULL)
		{
			del(newcontent);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, node);
		lst = lst->next;
	}
	return (result);
}
