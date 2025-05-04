/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:00:15 by rboulaga          #+#    #+#             */
/*   Updated: 2023/12/06 23:11:23 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;

	if (!lst || !del)
		return ;
	head = *lst;
	while (head)
	{
		*lst = head->next;
		del(head->content);
		free(head);
		head = *lst;
	}
	*lst = NULL;
}
