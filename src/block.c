/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:32:26 by jojo              #+#    #+#             */
/*   Updated: 2023/01/19 02:59:57 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block		*init_block(uint64_t addr, size_t free, size_t size, t_block *prev, t_block *next)
{
	t_block	*new = (t_block *)addr;

	new->magic = free;
	new->size = size;
	new->prev = prev;
	new->next = next;

	return (new);
}

t_block		*split_block(t_block *block, size_t size)
{
	t_block	*free;

	if (block->size - mod_base(size) < BLOCK_H){
		block->magic = (MAGIC | USED);
		return (block);
	}

	free = init_block(ADDR(block) + BLOCK_H + mod_base(size) , (MAGIC | FREE), \
		block->size - BLOCK_H - mod_base(size), block, block->next);

	if (free->next)
		free->next->prev = free;

	block = init_block(ADDR(block), (MAGIC | USED), mod_base(size), block->prev, free);
	
	return (block);
}

t_block		*new_block(t_page *page, size_t size)
{
	t_block	*block = FIRST(page);

	if (page->type == L)
		return (block);

	while (block){
		if (IS_FREE(block->magic) && (block->size >= mod_base(size)))
			break ;
		block = block->next;
	}

	if (block->size != mod_base(block->size)){
		P("FUCK\n")
		sleep(5);
	}
	if (!block){
		P("no block found\n")
		print_memory((void *)block, 32);
		return (NULL);
	}

	if ((ADDR(block) + mod_base(size) + BLOCK_H) > (ADDR(page) + PAGE_H + page->max)){
		P("block go outside range\n")
		print_memory((void *)block, 32);
		return (NULL);
	}

	return (split_block(block, size));
}