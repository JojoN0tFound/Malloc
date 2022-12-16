/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquivogn <jquivogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:55:01 by jquivogn          #+#    #+#             */
/*   Updated: 2022/12/16 21:10:02 by jquivogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void print_memory(const void *addr, size_t size)
{
	size_t printed;
	size_t i;
	const unsigned char* pc;
	int g;

	printed = 0;
	i = 0;
	pc = addr;
	while (i < size) {
		g = (*(pc+i) >> 4) & 0xf;
		g += g >= 10 ? 'a'-10 : '0';
		ft_putchar(g);
		printed++;
		g = *(pc+i) & 0xf;
		g += g >= 10 ? 'a'-10 : '0';
		ft_putchar(g);
		printed++;
		if (printed % 32 == 0)
			ft_putchar('\n');
		else if (printed % 4 == 0)
			ft_putchar(' ');
		i++;
	}
}

void	print_block(t_block *block, int nb)
{
	ft_putstr("=========BLOCK========\n");
	if (nb != -1) {
		ft_putstr("block nb: ");
		ft_putnbr(nb);
		ft_putchar('\n');
	}
	ft_putstr("block  addr: ");
	ft_putaddr((uint64_t)block);
	ft_putstr("\naddr  magic: ");
	ft_putaddr(block->magic);
	ft_putstr("\nblock size: ");
	ft_putnbr(block->size);
	ft_putstr("\nblock prev: ");
	ft_putaddr((uint64_t)block->prev);
	ft_putstr("\nblock next: ");
	ft_putaddr((uint64_t)block->next);
	ft_putstr("\n======================\n\n");
}

void	print_all_block(t_block *block)
{
	int i = 0;
	while (block) {
		print_block(block, i);
		block = block->next;
		i++;
	}
}