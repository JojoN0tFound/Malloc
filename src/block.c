/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:32:26 by jojo              #+#    #+#             */
/*   Updated: 2022/12/15 00:10:36 by jojo             ###   ########.fr       */
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

size_t		get_block_size(size_t size)
{
	if (size > TINY)
		return (SMALL);
	return (TINY);
}

t_block		*new_block(t_page *page, size_t size)
{
	int		isMiddle;
	t_block	*new;
	t_block	*tmp;

	isMiddle = FALSE;
	tmp = (t_block *)((uint64_t)page + PAGE_H);
	if (!IS_MAGIC(tmp->magic))
		return (init_block((uint64_t)tmp, size, NULL, NULL));
	while (tmp && tmp->next && ((USED & tmp->magic) == 2)) {
		if (((uint64_t)tmp->next - ((uint64_t)tmp + SIZE(MOD_BASE(tmp->size)))) > SIZE(MOD_BASE(size))) {
			isMiddle = TRUE;
			break ;
		}
		tmp = tmp->next;
	}
	if (((uint64_t)tmp + SIZE(MOD_BASE(tmp->size))) >= ((uint64_t)page + page->max + PAGE_H))
		return (NULL);
	new = init_block(((uint64_t)tmp + SIZE(MOD_BASE(tmp->size))), size, tmp, isMiddle ? tmp->next : NULL);
	tmp->next = new;
	return (new);
}