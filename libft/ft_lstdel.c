/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:42:02 by lseema            #+#    #+#             */
/*   Updated: 2020/12/11 22:12:27 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *cur;

	if (!del || !alst)
		return ;
	cur = *alst;
	while (cur != NULL)
	{
		del(cur->content, cur->content_size);
		free(cur);
		cur = cur->next;
	}
	*alst = NULL;
}
