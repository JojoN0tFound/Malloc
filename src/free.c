/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/15 01:40:45 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_page	**get_head(size_t size)
{
	if (size > SMALL)
		return (&g_store_mem.large);
	else if (size > TINY)
		return (&g_store_mem.small);
	else
		return (&g_store_mem.tiny);
}

void	free_block(t_block *block)
{
	block->magic = FREE;
	if (block->prev && block->next) {
		block->prev->next = block->next;
		block->next->prev = block->prev;
	}
	if (block->prev && !block->next) {
		block->prev->next = NULL;
	}
	if (!block->prev && block->next) {
		block->next->prev = NULL;
	}
}

void	free_page(t_block *block)
{
	t_page	**head;
	t_page	*page;
	t_page	*tmp;

	head = get_head(block->size);
	page = *head;
	while (page && (uint64_t)page > (uint64_t)block) {
		tmp = page;
		page = page->next;
	}
	if (!page)
		return ;
	page->space -= SIZE(MOD_BASE(block->size));
	free_block(block);
	if (page->space == 0) {
		if (*head == page)
			*head = page->next ? page->next : NULL;
		else
			tmp->next = page->next ? page->next : NULL;
		munmap(page, page->max);
	}
}

void	free(void *ptr)
{
	t_block	*block;

	if (ptr == NULL)
		return ;
	block = (t_block *)((uint64_t)ptr);
	free_page(block);
	return;
}