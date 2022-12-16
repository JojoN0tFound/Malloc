/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:32:26 by jojo              #+#    #+#             */
/*   Updated: 2022/12/16 22:17:46 by jquivogn         ###   ########.fr       */
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
	tmp = page->first;
	if (!tmp) {
		new = init_block(ADDR(page) + PAGE_H, size, NULL, NULL);
		page->first = new;
		return (new);
	}
	while (tmp && tmp->next && ((USED & tmp->magic) == 1)) {
		if (((uint64_t)tmp->next - ((uint64_t)tmp + SIZE(MOD_BASE(tmp->size)))) > SIZE(MOD_BASE(size))) {
			isMiddle = TRUE;
			break ;
		}
		tmp = tmp->next;
	}
	if ((ADDR(tmp) + SIZE(MOD_BASE(tmp->size))) >= (ADDR(page) + page->max + PAGE_H))
		return (NULL);
	// if (isMiddle) {
	// 	new = init_block((ADDR(tmp) + SIZE(MOD_BASE(tmp->size))), size, tmp, tmp->next);
	// 	tmp->next->size -= new->size;
	// }
	// else
	// 	new = init_block((ADDR(tmp) + SIZE(MOD_BASE(tmp->size))), size, tmp, NULL);
	new = init_block(((uint64_t)tmp + SIZE(MOD_BASE(tmp->size))), size, tmp, isMiddle ? tmp->next : NULL);
	tmp->next = new;
	return (new);
}