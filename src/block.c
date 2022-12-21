/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:32:26 by jojo              #+#    #+#             */
/*   Updated: 2022/12/21 09:47:56 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block		*init_block(uint64_t addr, size_t size, void *prev, void *next)
{
	t_block	*new;

	new = (t_block *)addr;
	new->magic = (MAGIC | USED);
	new->size = size;
	new->prev = prev;
	new->next = next;
	return (new);
}

t_block		*new_block(t_page *page, size_t size)
{
	int		isMiddle;
	t_block	*new;
	t_block	*tmp;

	isMiddle = FALSE;
	tmp = page->first;
	if (!tmp){
		new = init_block(ADDR(page) + PAGE_H, size, NULL, NULL);
		page->first = new;
		return (new);
	}
	while (tmp && tmp->next && ((USED & tmp->magic) == 1)){
		if ((ADDR(tmp->next) - (ADDR(tmp) + SIZE(tmp->size))) >= SIZE(size)) {
			isMiddle = TRUE;
			TOTO
			break ;
		}
		tmp = tmp->next;
	}
	if ((ADDR(tmp) + SIZE(MOD_BASE(tmp->size))) > (ADDR(page) + page->max + PAGE_H)){
		TEST
		return (NULL);
	}
	new = init_block((ADDR(tmp) + SIZE(MOD_BASE(tmp->size))), size, tmp, NULL);
	if (isMiddle){
		new->next = tmp->next;
		if (new->prev)
			new->prev->next = new;
		if (new->next)
			new->next->prev = new;
	}
	tmp->next = new;
	return (new);
}