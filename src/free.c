/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/19 01:43:14 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free_block(t_page **page, t_block *block)
{
	block->magic = FREE;
	block->size = 0;
	if (block->prev){
		block->prev->next = block->next;
	}
	if (block->next){
		block->next->prev = block->prev;
	}
	if ((*page)->first == block)
		(*page)->first = block->next;
	block->prev = NULL;
	block->next = NULL;
	block = NULL;
}

void	free_page(void *ptr)
{
	t_page	**head;
	t_page	*page;
	t_page	*tmp;
	t_block	*block;

	block = GOTO_H(ptr);
	if (!IS_MAGIC(block->magic) || (block->magic & FREE) == FREE)
		return ;
	head = get_head(block->size);
	page = *head;
	while (page && (uint64_t)(page) > (uint64_t)(block)){
		tmp = page;
		page = page->next;
	}
	if (!page)
		return ;
	page->space -= SIZE(MOD_BASE(block->size));
	free_block(head, block);
	if (page->space == 0){
		if (*head == page)
			*head = page->next ? page->next : NULL;
		else
			tmp->next = page->next ? page->next : NULL;
		munmap(page, page->max);
		return ;
	}
}

void	free(void *ptr)
{
	if (!ptr){
		return ;
	}
	free_page(ptr);
	return;
}