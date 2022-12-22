/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:32:26 by jojo              #+#    #+#             */
/*   Updated: 2022/12/22 20:40:59 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block		*init_block(uint64_t addr, size_t free, size_t size, void *prev, void *next)
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

	free = init_block(MOD_BASE(SIZE(ADDR(block)) + size) , (MAGIC | FREE), \
		block->size - SIZE(size), block, block->next);
	block = init_block(ADDR(block), (MAGIC | USED), size, block->prev, free);
	return (block);
}

t_block		*merge_block(t_block *block, t_block *merge)
{
	merge->magic = FREE;
	block = init_block(ADDR(block), (MAGIC | FREE), block->size + SIZE(merge->size), \
		block->prev, merge->next);
	return (block);
}

t_block		*defragment(t_block *block)
{
	if (block->prev && (block->prev->magic & FREE) == 2)
		block = merge_block(block->prev, block);
	if (block->next && (block->next->magic & FREE) == 2)
		block = merge_block(block, block->next);
	return (block);
}

t_block		*new_block(t_page *page, size_t size)
{
	t_block		*block;

	block = FIRST(page);
	while (block){
		if ((block->magic & FREE) == 2 && block->size >= SIZE(size))
			break ;
		block = block->next;
	}
	if (!block)
		return (NULL);
	block = split_block(block, size);
	return (block);
}