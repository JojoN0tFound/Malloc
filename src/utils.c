/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:40:31 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/08 20:11:33 by jojo             ###   ########.fr       */
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
		return (page_base(SIZE(SMALL)));
	else if (get_block_size(size) == TINY)
		return (page_base(SIZE(TINY)));
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

int			check_ptr(void *ptr)
{
	if (!ptr){
		// ft_putstr("[NO PTR]\n");
		return (FALSE);
	}
	if (!IS_MAGIC((GOTO_H(ptr))->magic)){
		// ft_putstr("[NO MAGIC]\n");
		return (FALSE);
	}
	if (((GOTO_H(ptr))->magic & FREE) == FREE){
		// ft_putstr("[ALREADY FREE]\n");
		return (FALSE);
	}
	return (TRUE);
}