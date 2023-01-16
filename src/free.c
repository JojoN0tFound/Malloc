/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/16 01:10:29 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free_page(t_page *page)
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
	munmap(page, page->max + PAGE_H);
}

t_block		*merge_block(t_block *block, t_block *merge)
{
	block = init_block(ADDR(block), (MAGIC | FREE), \
		mod_base(block->size) + mod_base(SIZE(merge->size)), block->prev, merge->next);
	if (block->prev)
		block->prev->next = block;
	if (merge->next)
		merge->next->prev = block;
	merge = init_block(ADDR(merge), FREE, 0, NULL, NULL);
	return (block);
}

t_block		*defragment(t_block *block)
{
	if (block->prev && IS(block->prev->magic, FREE))
		block = merge_block(block->prev, block);
	if (block->next && IS(block->next->magic, FREE))
		block = merge_block(block, block->next);
	block->magic = (MAGIC | FREE);
	return (block);
}

int		free_block(void *ptr)
{
	t_page	*page;
	t_block	*block;

	block = GOTO_H(ptr);
	if (!IS_MAGIC(block->magic))
		return (FALSE);
	page = g_first_page;
	while (page){
		if (ADDR(block) > ADDR(page) && ADDR(block) < (ADDR(page) + page->max + PAGE_H))
			break ;
		page = page->next;
	}
	if (!page)
		return (FALSE);
	block->size = mod_base(block->size);
	block = defragment(block);
	if (IS(block->magic, FREE) && block->size == page->max)
		free_page(page);
	return (TRUE);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&mutex);
	F_S
	if (ptr)
		free_block(ptr);
	F_E
	pthread_mutex_unlock(&mutex);
}