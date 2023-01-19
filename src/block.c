/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:32:26 by jojo              #+#    #+#             */
/*   Updated: 2023/01/19 17:32:37 by jojo             ###   ########.fr       */
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

	if (block->size - size < BLOCK_H){
		block->magic = (MAGIC | USED);
		return (block);
	}

	free = init_block(ADDR(block) + BLOCK_H + size , (MAGIC | FREE), \
		block->size - BLOCK_H - size, block, block->next);

	if (free->next)
		free->next->prev = free;

	block = init_block(ADDR(block), (MAGIC | USED), size, block->prev, free);
	
	return (block);
}
