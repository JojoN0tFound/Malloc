/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:40:31 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/30 06:21:12 by jquivogn         ###   ########.fr       */
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
	if (size > SMALL)
		return (size);
	else if (size > TINY)
		return (SMALL);
	return (TINY);
}

size_t		get_page_size(size_t size)
{
	if (get_block_size(size) == SMALL)
		return (26 * getpagesize());
	else if (get_block_size(size) == TINY)
		return (4 * getpagesize());
	else
		return (page_base(SIZE(size) + PAGE_H));
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
	int	ret;

	ret = size % 16;
	ret = ret == 0 ? 0 : 16 - ret;
	return (size + ret);
}

int			is_continuous_space(t_page *page, size_t size)
{
	t_block	*block;

	block = FIRST(page);
	while (block){
		if ((block->magic & FULL) == FULL)
			return (FALSE);
		if ((block->magic & FREE) == FREE && block->size >= mod_base(SIZE(size)))
			return (TRUE);
		block = block->next;
	}
	return (FALSE);
}