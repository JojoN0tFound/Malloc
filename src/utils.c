/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:40:31 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/21 10:30:32 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_page	**get_head(size_t size)
{
	if (size > SMALL)
		return (&g_store_mem.large);
	else if (size > TINY)
		return (&g_store_mem.small);
	else
		return (&g_store_mem.tiny);
}

size_t		get_block_size(size_t size)
{
	if (size > TINY)
		return (SMALL);
	return (TINY);
}

size_t		page_base(size_t size)
{
	size_t	size_page;
	size_t	need;

	need = size + PAGE_H;
	size_page = getpagesize();
	return (((need / size_page) + 1) * size_page);
}

size_t		mod_base(size_t size)
{
	return (((size / 16) + 1) * 16);
}

int		is_continuous_space(t_page *page, size_t size)
{
	t_block	*block;

	if (!(page->first))
		return (TRUE);
	block = page->first;
	while (block && block->next && ((USED & block->magic) == 1)){
		if ((ADDR(block->next) - (ADDR(block) + SIZE(block->size))) >= SIZE(size)){
			return (TRUE);
		}
		block = block->next;
	}
	if ((ADDR(block) + SIZE(mod_base(block->size))) <= (ADDR(page) + page->max + PAGE_H)){
		return (TRUE);
	}
	return (FALSE);
}