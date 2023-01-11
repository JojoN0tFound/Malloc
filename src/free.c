/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/11 22:16:06 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free_page(t_page *page)
{
	t_page	*prev;

	prev = g_first_page;
	if (prev == page){
		g_first_page = page->next;
	}
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
	merge->magic = FREE;
	block = init_block(ADDR(block), (MAGIC | FREE), \
		mod_base(block->size) + mod_base(SIZE(merge->size)), block->prev, merge->next);
	if (block->prev)
		block->prev->next = block;
	if (merge->next)
		merge->next->prev = block;
	return (block);
}

t_block		*defragment(t_block *block)
{
	if (block->prev && (block->prev->magic & FREE) == FREE)
		block = merge_block(block->prev, block);
	if (block->next && (block->next->magic & FREE) == FREE)
		block = merge_block(block, block->next);
	block->magic = (MAGIC | FREE);
	return (block);
}

int		free_block(void *ptr)
{
	t_page	*page;
	t_block	*block;

	block = GOTO_H(ptr);
	page = g_first_page;
	while (page){
		if (ADDR(block) > ADDR(page) && ADDR(block) < (ADDR(page) + page->max + PAGE_H))
			break ;
		page = page->next;
	}
	if (!page)
		return (FALSE);
	if (get_type(block->size) != page->type){
		// show_alloc_mem();
		// P("      Type: ")
		// if (page->type == T)
		// 	ft_putstr("TINY");
		// else if (page->type == S)
		// 	ft_putstr("SMALL");
		// else if (page->type == L)
		// 	ft_putstr("LARGE");
		// N
		// print_block(block, -5);
	}
	block->size = mod_base(block->size);
	block = defragment(block);
	if ((block->magic & FREE) == FREE && block->size == page->max)
		free_page(page);
	return (TRUE);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&mutex);
	if (check_ptr(ptr))
		free_block(ptr);
	pthread_mutex_unlock(&mutex);
}