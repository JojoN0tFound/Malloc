/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:40:31 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/10 21:06:43 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_page	*get_head(size_t size)
{
	if (size > SMALL){
		ft_putstr("[LARGE:");
		ft_putaddr(ADDR(g_store_mem.large));
		N
		return (g_store_mem.large);
	}
	else if (size > TINY){
		ft_putstr("[SMALL:");
		ft_putaddr(ADDR(g_store_mem.small));
		N
		return (g_store_mem.small);
	}
	else{
		ft_putstr("[TINY:");
		ft_putaddr(ADDR(g_store_mem.tiny));
		N
		return (g_store_mem.tiny);
	}
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
		return (SMALL_PAGE);
		// return (page_base(SIZE(SMALL) * 100));
	else if (get_block_size(size) == TINY)
		return (TINY_PAGE);
		// return (page_base(SIZE(TINY) * 100));
	else
		return (page_base(SIZE(size)));
}

size_t		page_base(size_t size)
{
	size_t	size_page;
	int		ret;

	size_page = getpagesize();
	ret = size % size_page;
	ret = ret == 0 ? 0 : size_page - ret;
	return (size + ret);
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