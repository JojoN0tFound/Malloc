/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/19 19:30:48 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		free_page(t_page *page)
{
	t_page	*prev = g_first_page;

	if (prev == page)
		g_first_page = page->next;
	else {
		while (prev && prev->next){
			if (prev->next == page)
				break ;
			prev = prev->next;
		}
		prev->next = page->next;
	}

	return (munmap(page, page->max + PAGE_H + BLOCK_H));
}

t_block		*merge_block(t_block *block, t_block *merge)
{
	block = init_block(ADDR(block), (MAGIC | FREE), \
		block->size + merge->size + BLOCK_H, block->prev, merge->next);

	if (merge->next)
		block->next->prev = block;

	merge = init_block(ADDR(merge), FREE, 0, NULL, NULL);

	return (block);
}

t_block		*defragment(t_block *block)
{
	if (block->prev && IS_FREE(block->prev->magic))
		block = merge_block(block->prev, block);

	if (block->next && IS_FREE(block->next->magic))
		block = merge_block(block, block->next);

	block->magic = (MAGIC | FREE);
	
	return (block);
}

int		free_block(void *ptr)
{
	t_block	*block = GOTO_H(ptr);
	t_page	*page;

	if (!(page = find_block_page(ADDR(block))))
		return (FALSE);

	if (!IS_MAGIC(block->magic) || IS_FREE(block->magic))
		return (FALSE);

	if (page->type == L)
		return (free_page(page) == 0);
	
	block->size = mod_base(block->size);
	page->fill += (block->size + BLOCK_H);

	if (page->max == page->fill)
		return (free_page(page) == 0);
	
	block = defragment(block);

	return (TRUE);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&mutex);

	if (ptr)
		free_block(ptr);

	pthread_mutex_unlock(&mutex);
}