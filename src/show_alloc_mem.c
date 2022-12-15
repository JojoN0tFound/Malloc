/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:37:24 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/15 00:09:42 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	show_block(t_block *block)
{
	ft_putaddr((uint64_t)block + BLOCK_H);
	ft_putstr(" - ");
	ft_putaddr((uint64_t)block + SIZE(block->size));
	ft_putstr(" : ");
	ft_putnbr(block->size);
	ft_putstr(" bytes\n");
}

size_t	show_page(t_page **head_page, char *type)
{
	t_page	*tmp;
	t_block	*block;
	size_t	total;

	total = 0;
	tmp = *head_page;
	while (tmp) {
		ft_putstr(type);
		ft_putstr(" : ");
		ft_putaddr((uint64_t)tmp);
		ft_putchar('\n');
		block = (t_block *)((uint64_t)tmp + PAGE_H);
		while (block) {
			show_block(block);
			total += block->size;
			block = block->next;
		}
		tmp = tmp->next;
	}
	return (total);
}

void	show_alloc_mem()
{
	size_t	total;
	t_page	*tiny;
	t_page	*small;
	t_page	*large;

	total = 0;
	tiny = g_store_mem.tiny;
	small = g_store_mem.small;
	large = g_store_mem.large;
	if (tiny)
		total += show_page(&tiny, "TINY");
	if (small)
		total += show_page(&small, "SMALL");
	if (large)
		total += show_page(&large, "LARGE");
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" bytes\n");
}