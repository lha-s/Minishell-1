/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap_bonus.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 18:14:42 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 15:29:36 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *begin;
	t_list *tmp;
	t_list *prev;

	if (lst == NULL || !(begin = ft_lstnew(lst->content)))
		return (NULL);
	begin->content = (*f)(lst->content);
	tmp = lst->next;
	prev = begin;
	while (tmp != NULL)
	{
		if (!(new = ft_lstnew(tmp->content)))
		{
			ft_lstclear(&begin, (*del));
			return (NULL);
		}
		new->content = (*f)(new->content);
		prev->next = new;
		prev = new;
		tmp = tmp->next;
	}
	return (begin);
}
