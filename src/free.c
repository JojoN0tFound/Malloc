/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:19:05 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/10 20:56:40 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		block_in_page(t_page *page, uint64_t target)
{
	t_block	*block;

	block = FIRST(page);
	while (block){
		if (ADDR(block) == target)
		// if (ADDR(block) == target && (block->magic & USED) == USED)
			return (TRUE);
		block = block->next;
	}
	return (FALSE);
}

void	free_page(t_page *head, t_page *page)
{
	t_page	*prev;

	prev = head;
	if (head == page){
		if (page->space == TINY_PAGE)
			g_store_mem.tiny = page->next;
		if (page->space == SMALL_PAGE)
			g_store_mem.small = page->next;
		else
			g_store_mem.large = page->next;
	}
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

int		free_block(void *ptr)
{
	t_page	*page;
	t_block	*block;
	t_page *head;

	block = GOTO_H(ptr);
	head = get_head(block->size);
	page = head;
	while (page){
		if (ADDR(block) > ADDR(page) && ADDR(block) < (ADDR(page) + page->space + PAGE_H))
		// if (block_in_page(page, ADDR(block)))
			break ;
		page = page->next;
	}
	if (!page){
		// print_all_block(block);
		if (block->size == 304)
			show_alloc_mem();
		print_block(block, -5);
		// ft_putulnbr(block->size);
		// N
		// ft_putaddr(ADDR(block));
		// N
		// print_memory((void *)block, 32);
		ft_putstr("[FREE NO PAGE]\n");
		return (FALSE);
	}
	block->size = mod_base(block->size);
	block = defragment(block);
	if ((block->magic & FREE) == FREE && block->size == page->space)
		free_page(head, page);
	return (TRUE);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&mutex);
	// ft_putstr("[START FREE]\n");
	if (!check_ptr(ptr)){
		pthread_mutex_unlock(&mutex);
		return ;
	}
	free_block(ptr);
	// ft_putstr("[E--------------------F]\n");
	pthread_mutex_unlock(&mutex);
}