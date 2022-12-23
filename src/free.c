/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julesqvgn <julesqvgn@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/23 15:09:29 by julesqvgn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		block_in_page(t_page *page, uint64_t target)
{
	t_block	*block;

	block = FIRST(page);
	while (block){
		if (ADDR(block) == target && (block->magic & FREE) == 2)
			return (TRUE);
		block = block->next;
	}
	return (FALSE);
}

void	free_page(t_page **head, t_page *page)
{
	t_page	*prev;

	prev = *head;
	if (*head == page)
		*head = page->next;
	else {
		while (prev && prev->next){
			if (prev->next == page)
				break ;
			prev = prev->next;
		}
		prev->next = page->next;
	}
	munmap(page, page->space);
}

void	free_block(void *ptr)
{
	t_page	**head;
	t_page	*page;
	t_block	*block;

	block = GOTO_H(ptr);
	if (!IS_MAGIC(block->magic) || (block->magic & FREE) == FREE)
		return ;
	head = get_head(block->size);
	page = *head;
	while (page){
		if (block_in_page(page, ADDR(block)))
			break ;
		page = page->next;
	}
	if (!page)
		return ;
	page->space += mod_base(SIZE(block->size));
	block = defragment(block);
	//condition may not work
	//should try with MAX define and get_size
	if (((FIRST(page))->magic & FREE) == FREE && !(FIRST(page))->next)
		free_page(head, page);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&mutex);
	if (!ptr){
		pthread_mutex_unlock(&mutex);
		return ;
	}
	free_block(ptr);
	pthread_mutex_unlock(&mutex);
}