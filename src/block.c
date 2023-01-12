/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:32:26 by jojo              #+#    #+#             */
/*   Updated: 2023/01/12 13:28:19 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block		*init_block(uint64_t addr, size_t free, size_t size, t_block *prev, t_block *next)
{
	t_block	*new;

	new = (t_block *)addr;
	new->magic = free;
	new->size = size;
	new->prev = prev;
	new->next = next;
	return (new);
}

t_block		*split_block(t_block *block, size_t size)
{
	t_block	*free;

	if (block->size - mod_base(size) <= BLOCK_H){
		block->magic = (MAGIC | USED);
		return (block);
	}
	free = init_block(mod_base(SIZE(ADDR(block)) + size) , (MAGIC | FREE), \
		block->size - mod_base(SIZE(size)), block, block->next);
	if (free->next)
		free->next->prev = free;
	return (init_block(ADDR(block), (MAGIC | USED), size, block->prev, free));
}

t_block		*new_block(t_page *page, size_t size)
{
	t_block		*block;

	block = FIRST(page);
	while (block){
		if (IS(block->magic, FREE) && block->size >= mod_base(SIZE(size)))
			break ;
		block = block->next;
	}
	if (!block)
		return (NULL);
	return (split_block(block, size));
}