/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:37:24 by jquivogn          #+#    #+#             */
/*   Updated: 2023/01/11 19:31:12 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	show_block(t_block *block, t_type type)
{
	if ((type == T && block->size > TINY) || (type == S && (block->size <= TINY || block->size > SMALL)) || (type == L && block->size <= SMALL))
	{
		P(RED)
		ft_putaddr(ADDR(block) + BLOCK_H);
		ft_putstr(" - ");
		ft_putaddr(ADDR(block) + SIZE(block->size));
		ft_putstr(" : ");
		ft_putnbr(block->size);
		ft_putstr(" bytes\n");
		P(WHI)
	}
}

size_t	show_page(t_page *head_page)
{
	t_page	*tmp;
	t_block	*block;
	size_t	total;

	total = 0;
	tmp = head_page;
	while (tmp){
		if (tmp->type == T)
			ft_putstr("TINY");
		else if (tmp->type == S)
			ft_putstr("SMALL");
		else if (tmp->type == L)
			ft_putstr("LARGE");
		ft_putstr(" : ");
		ft_putaddr(ADDR(tmp));
		ft_putchar('\n');
		block = FIRST(tmp);
		while (block){
			if ((block->magic & USED) == USED){
				show_block(block, tmp->type);
				total += block->size;
			}
			block = block->next;
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
	if (alloc)
		total += show_page(alloc);
	if (total != 0){
		ft_putstr("Total : ");
		ft_putnbr(total);
		ft_putstr(" bytes\n");
	}
	// pthread_mutex_unlock(&mutex);
}