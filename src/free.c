/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/19 02:34:58 by jojo             ###   ########.fr       */
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

	return (munmap(page, page->max + PAGE_H));
}

t_block		*merge_block(t_block *block, t_block *merge)
{
	block = init_block(ADDR(block), (MAGIC | FREE), \
		block->size + merge->size + BLOCK_H, block->prev, merge->next);

	// if (block->prev)
	// 	block->prev->next = block;

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
	t_page	*page = g_first_page;
	t_block	*block = GOTO_H(ptr);

	if (!IS_MAGIC(block->magic)){
		P("NOT A MAGIC BLOCK\n")
		return (FALSE);
	}

	if (IS_FREE(block->magic)){
		P("double free\n");
		return (FALSE);
	}

	// print_block(block, ite--);

	while (page){
		if ((ADDR(block) > ADDR(page)) && (ADDR(block) < (ADDR(page) + page->max + PAGE_H)))
			break ;
		page = page->next;
	}

	if (!page){
		P("NO PAGE found for free\n")
		print_memory((void *)block, 32);
		return (FALSE);
	}

	if (page->type == L){
		return (free_page(page) == 0);
	}
	
	block->size = mod_base(block->size);
	block = defragment(block);
	page->fill--;

	if (block->size % 16 != 0){
		TEST
		sleep(5);
	}
	if (page->fill == 0)
		free_page(page);

	return (TRUE);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&mutex);

	// F_S
	if (ptr)
		free_block(ptr);

	// F_E
	pthread_mutex_unlock(&mutex);
}