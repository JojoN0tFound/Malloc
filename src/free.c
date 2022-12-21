/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/21 09:39:13 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		block_in_page(t_page *page, uint64_t target)
{
	t_block	*block;

	block = page->first;
	while (block){
		if (ADDR(block) == target)
			return (TRUE);
		block = block->next;
	}
	return (FALSE);
}

void	free_block(t_page **page, t_block *block)
{
	// print_block(block, -1);
	block->magic = FREE;
	block->size = 0;
	if (!block->prev && block->next){
		(*page)->first = block->next;
		block->next->prev = NULL;
	}
	if (!block->next && block->prev){
		block->prev->next = NULL;
	}
	if (block->prev && block->next){
		block->next->prev = block->prev;
		block->prev->next = block->next;
	}
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
	ft_putstr("---------------\n");
	ft_putulnbr(block->size);
	ft_putstr("\n---------------\n");
	head = get_head(block->size);
	page = *head;
	while (page && !block_in_page(page, ADDR(block))){
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
		// show_alloc_mem();
		return ;
	}
}

void	*aligned_alloc( size_t alignment, size_t memorySize)
{
	TOTO
	return (NULL);
}


void	free(void *ptr)
{
	ft_putstr("================================= FREE ===============================\n");
	// ft_putstr("\n---------\n");
	// show_alloc_mem();
	pthread_mutex_lock(&mutex);
	if (!ptr){
		pthread_mutex_unlock(&mutex);
		return ;
	}
	free_page(ptr);
	ft_putstr("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	pthread_mutex_unlock(&mutex);
}