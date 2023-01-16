/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:32:26 by jojo              #+#    #+#             */
/*   Updated: 2023/01/16 17:46:46 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block		*init_block(uint64_t addr, size_t free, size_t size, t_block *prev, t_block *next)
{
	t_block	*new;

	new = (t_block *)addr;
	if ((new->prev || new->next) && !IS_MAGIC(new->magic)){
		ft_putaddr(ADDR(prev));
		N
		print_block(new, 90);
		N
	}
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
	// if (size <= TINY)
	// 	print_memory((void *)(ADDR(block)-32), SIZE(SIZE(block->size)));
	// N
	// print_block(block, 2);
	// ft_putulnbr(size);
	// N
	free = init_block(mod_base(ADDR(block) + SIZE(size)) , (MAGIC | FREE), \
		block->size - mod_base(SIZE(size)), block, block->next);
	// print_block(free, 1);
	if (free->next)
		free->next->prev = free;
	return (init_block(ADDR(block), (MAGIC | USED), size, block->prev, free));
}

t_block		*new_block(t_page *page, size_t size)
{
	t_block	*block = FIRST(page);

	while (block){
		if (IS_FREE(block->magic) && block->size >= mod_base(SIZE(size)))
			break ;
		block = block->next;
	}
	if (!block)
		return (NULL);
	return (split_block(block, size));
}