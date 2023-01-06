/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/06 18:49:45 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		block_in_page(t_page *page, uint64_t target)
{
	t_block	*block;

	block = FIRST(page);
	while (block){
		if (ADDR(block) == target && (block->magic & USED) == USED)
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
	munmap(page, page->space + PAGE_H);
}

t_block		*merge_block(t_block *block, t_block *merge)
{
	merge->magic = FREE;
	block = init_block(ADDR(block), (MAGIC | FREE), mod_base(block->size) + mod_base(SIZE(merge->size)), \
		block->prev, merge->next);
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

void	free_block(void *ptr)
{
	t_page	**head;
	t_page	*page;
	t_block	*block;

	block = GOTO_H(ptr);
	if (!IS_MAGIC(block->magic)){
		ft_putstr("NOOOOPPPPP\n");
		return ; 
	}
	head = get_head(block->size);
	page = *head;
	while (page){
		if (block_in_page(page, ADDR(block)))
			break ;
		page = page->next;
	}
	if (!page){
		ft_putulnbr(block->size);
		N
		ft_putaddr(ADDR(block));
		N
		show_alloc_mem();
		ft_putstr("[FREE NO PAGE]\n");
		return ;
	}
	block->size = mod_base(block->size);
	block = defragment(block);
	if ((block->magic & FREE) == FREE && block->size == page->space)
		free_page(head, page);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&mutex);
	ft_putstr("[START FREE]\n");
	if (!ptr){
		ft_putstr("[FREE FAIL]\n");
		pthread_mutex_unlock(&mutex);
		return ;
	}
	free_block(ptr);
	ft_putstr("[E--------------------F]\n");
	pthread_mutex_unlock(&mutex);
}