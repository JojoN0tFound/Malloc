/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:37:24 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/18 23:41:36 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		show_block(t_block *block)
{
	ft_putaddr(ADDR(block) + BLOCK_H);
	ft_putstr(" - ");
	ft_putaddr(ADDR(block) + BLOCK_H + block->size);
	ft_putstr(" : ");
	ft_putnbr(block->size);
	ft_putstr(" bytes\n");
	return (block->size);
}

size_t	show_page(t_page *head_page, t_type type)
{
	t_page	*tmp;
	t_block	*block;
	size_t	total;

	total = 0;
	tmp = head_page;
	while (tmp){
		if (tmp->type == type){
			if (tmp->type == T)
				ft_putstr("\033[0;36mTINY");
			else if (tmp->type == S)
				ft_putstr("\033[1;34mSMALL");
			else if (tmp->type == L)
				ft_putstr("\033[0;32mLARGE");
			P(WHI)
			ft_putstr(" : ");
			ft_putaddr(ADDR(tmp));
			ft_putchar('\n');
			block = FIRST(tmp);
			while (block){
				if (IS_USED(block->magic))
					total += show_block(block);
				block = block->next;
			}
		}
		tmp = tmp->next;
	}
	return (total);
}

void	show_alloc_mem()
{
	size_t	total;
	t_page	*alloc;

	// pthread_mutex_lock(&mutex);
	total = 0;
	alloc = g_first_page;
	if (alloc){
		total += show_page(alloc, T);
		total += show_page(alloc, S);
		total += show_page(alloc, L);
	}
	if (total != 0){
		P(RED)
		ft_putstr("Total\033[0m : ");
		ft_putnbr(total);
		ft_putstr(" bytes\n");
	}
	// pthread_mutex_unlock(&mutex);
}